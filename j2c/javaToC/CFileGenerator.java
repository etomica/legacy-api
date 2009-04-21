package javaToC;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javaToC.SignatureUtilities.MethodSignatureItem;


public class CFileGenerator extends FileGenerator {

    private ArrayList<String> includeList;
    private ClassTypeC[] cct;
    private ClassTypeJava[] jct;
    private int classIndex;
    private InputParameters inputParms;
    private String objectPersistHash;
    private String methodID = new String("myMethodID");
    private ImportResolver importResolver;

    
    CFileGenerator(File includeFile, ClassTypeC[] cc, ClassTypeJava[] jc, int idx, InputParameters ip,
                   String op, ImportResolver ir) {

        cct = cc;
        jct = jc;
        inputParms = ip;
        importResolver = ir;
        indentLevel = 0;
        objectPersistHash = op;
        classIndex = idx;
        
        
        try {
            writer = new BufferedWriter(new FileWriter(includeFile));
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    /**
     * 
     */
    public void writeCFile() {
        
        String packageName = new String(jct[classIndex].getPackageName());
        while(packageName.contains(".")) packageName = packageName.replace(".", "/");

        try {
            boolean returningCharPointer = false;
        	for(int i = 0; i < cct[classIndex].getMethodReturn().length; i++) {
        		if(cct[classIndex].getMethodReturn()[i].compareTo("char *") == 0) {
        			returningCharPointer = true;
        			break;
        		}
        	}
        	
        	if(returningCharPointer) {
        		writeLine("#include \"string.h\"");
        		writeLine("#include \"malloc.h\"");        		
        	}
            writeLine("#include <typeinfo>");
            
        	for(int i = 0; i < importResolver.getSourceFileList().size(); i++) {
        	    writeLine("#include \"" + importResolver.getSourceFileList().get(i) + ".h\"");
        	}
        	
            includeList = new ArrayList<String>();
            includeList.add(cct[classIndex].getClassname());
            includeList.add(objectPersistHash);
            
            // for each return type, include all subclasses
            for(int i = 0; i < cct[classIndex].getMethodReturn().length; i++) {
                String ret = new String(cct[classIndex].getMethodReturn()[i]);
                // Remove pointer notation
                ret = ret.replace("*", "");
                // Remove array notation
                ret = ret.replace("[]", "");
                ret = StringUtilities.removeEdgeWhitespace(ret);
//System.out.println("ret ->" + ret + "<-");
                if(!TypeConversion.isBasicCType(ret) && ret.compareTo("") != 0) {
                    try {
                        int retIdx = getCClassIndex(ret);
//System.out.println("idx = " + retIdx);
                        for(int j = 0; j < cct[retIdx].getSubclassList().length; j++) {
//System.out.println("  possible : " + cct[retIdx].getSubclassList()[j]);
                            boolean addInclude = true;
                            for(int k = 0; k < includeList.size(); k++) {
                                if(cct[retIdx].getSubclassList()[j].compareTo((String)includeList.get(k)) == 0) {
                                    addInclude = false;
                                    break;
                                }
                            }
                            if(addInclude) includeList.add(cct[retIdx].getSubclassList()[j]);
                        }
                    }
                    catch (ClassNotFoundException ex) {
                        System.out.println("Treating class like it is an inner class.");
                        //ex.printStackTrace();
                    }
                }
            }

            for(int i = 0; i < includeList.size(); i++) {
                writeLine("#include \"" + (String)includeList.get(i) + ".h\"");
            }
            
            if(inputParms.useNamespace()) {
                writer.newLine();
                writeLine("namespace " + cct[classIndex].getNamespace() + " {");
                writer.newLine();
                indentLevel++;
            }
            
            if(!cct[classIndex].isPureVirtualClass()) {
                
                // create ctor(jobject)
                String ctorDeclare;
                ctorDeclare = new String(cct[classIndex].getClassname() + "::" + cct[classIndex].getClassname() + "(jobject jobj)");
                if(cct[classIndex].getExtends().length == 0)
                    ctorDeclare = ctorDeclare.concat(" {");
                else {
                    for(int i = 0; i < cct[classIndex].getExtends().length; i++) {
                        ctorDeclare = ctorDeclare.concat(" : " + cct[classIndex].getExtends()[i] + "(jobj)");
                    }
                    ctorDeclare = ctorDeclare.concat(" {");
                }
                writeLine(ctorDeclare);
                
                indentLevel++;
                writeLine("myObject = jobj;");
                writeLine("if(typeid(*this) == typeid(" + cct[classIndex].getClassname() + ")) {");
                
                indentLevel++;
    
                writeGetJVM(packageName);

                writeLine("jclass myClass = (jenv)->FindClass(\"" + cct[classIndex].getJNIName() + "\");");
                writeHashCode("myObject");
                
                writeLine(objectPersistHash + "::addEntry(hashValue, this);");
                
                indentLevel--; 
                writeLine("}");
                
                indentLevel--;
                writeLine("}");
                writer.newLine();

                // Ctors
                for(int i = 0; i < cct[classIndex].getNumberOfCtors(); i++) {
                    String methodDeclare = cct[classIndex].getClassname() + "::" + cct[classIndex].getClassname() + "(";
                    MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(cct[classIndex].getCtorSignature()[i]);
                    methodDeclare = methodDeclare.concat(SignatureUtilities.getSignature(mySigItems));
                    methodDeclare = methodDeclare.concat(") {");

                    writeLine(methodDeclare);
                    
                    indentLevel++;
                    
    
                    writeLine("if(typeid(*this) == typeid(" + cct[classIndex].getClassname() + ")) {");
                    indentLevel++;
                    
                    writeGetJVM(packageName);
                    
                    writeLine("jclass myClass = (jenv)->FindClass(\"" + cct[classIndex].getJNIName() + "\");");
//System.out.println("CTOR : " + cct[classIndex].getCtorSignature()[i]);
                    writeLine(constructMethodID(cct[classIndex].getClassname(), "", cct[classIndex].getCtorSignature()[i], false));
                    constructAndWriteMethodCall("", mySigItems/*cct[classIndex].getCtorSignature()[i]*/, false);
    
                    indentLevel--; 
                    writeLine("}");
                    
                    indentLevel--;
    
                    writeLine("}");
                    writer.newLine();
                }
 
                // setJavaObject method
                writeLine("void " + cct[classIndex].getClassname() + "::setJavaObject(jobject jobj) {");
                indentLevel++;
                writeLine("myObject = jobj;");
                for(int i = 0; i < cct[classIndex].getExtends().length; i++) {
                    writeLine(cct[classIndex].getExtends()[i] + "::setJavaObject(myObject);");
                }
                indentLevel--;
                writeLine("}");
                
            }
            
            // public methods
            // It is possible that the class does not have a public ctor.
            // In that case, would need to add one for creation of myObject
            // and inclusion in proxy hash?
            if(cct[classIndex].getMethodName().length > 0) {
                for(int i = 0; i < cct[classIndex].getMethodName().length; i++) {

                    String methodDeclare = cct[classIndex].getMethodReturn()[i] + " " +
                        cct[classIndex].getClassname() + "::" +
                        cct[classIndex].getMethodName()[i] + "(";
                    MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(cct[classIndex].getMethodSignature()[i]);
                    methodDeclare = methodDeclare.concat(SignatureUtilities.getSignature(mySigItems));

                    methodDeclare = methodDeclare.concat(") {");
                    
                    writeLine(methodDeclare);
                    writer.newLine();
                    
                    indentLevel++;
                    
                    writeGetJVM(packageName);
                    
                    writeLine("jclass myClass = (jenv)->FindClass(\"" + cct[classIndex].getJNIName() + "\");");
                    writeLine(constructMethodID(cct[classIndex].getMethodName()[i],
                                                cct[classIndex].getMethodReturn()[i],
                                                cct[classIndex].getMethodSignature()[i],
                                                cct[classIndex].getStatic()[i]));
//System.out.println("Method Return : " + cct[classIndex].getMethodReturn()[i]);
                    constructAndWriteMethodCall(cct[classIndex].getMethodReturn()[i],
                                                mySigItems/*cct[classIndex].getMethodSignature()[i]*/,
                                                cct[classIndex].getStatic()[i]);

                    indentLevel--;

                    writeLine("}");
                    writer.newLine();
                }
            }
            
            if(inputParms.useNamespace()) {
                writer.newLine();
                writeLine("} // End namespace");
                indentLevel--;
            }

            writer.flush();

        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    /**
     * The return value of the call to method ID is assigned to the value of
     * this classes methodID string.
     * @param methodName
     * @param methodReturn
     * @param signature
     * @param isStatic
     * @return Returns a string containing the line of code required to get the
     *         Java method ID for the method name/signature/return passed in.
     */
    private String constructMethodID(String methodName, String methodReturn,
                                     String signature, boolean isStatic) {

        return constructMethodID(methodName, methodReturn, signature, methodID, isStatic);
    }

    /**
     * 
     * @param methodName
     * @param methodReturn
     * @param signature
     * @param isStatic
     * @param varName The return value of the call to method ID is assigned to the value of
     *        this string.
     * @return Returns a string containing the line of code required to get the
     *         Java method ID for the method name/signature/return passed in.
     */
    private String constructMethodID(String methodName, String methodReturn,
                                     String signature, String varName, boolean isStatic) {
        
        String myVMReturn = new String(methodReturn);
        
        // Change local copy of ctor return type
        if(methodReturn.compareTo("") == 0) myVMReturn = "void";
        
        String myLine;
        if(isStatic)
            myLine = new String("jmethodID " + varName + " = (jenv)->GetStaticMethodID(myClass, ");
        else
            myLine = new String("jmethodID " + varName + " = (jenv)->GetMethodID(myClass, ");
        
//System.out.println("METHOD : " + methodName);
//System.out.println("  signature : " + signature);

//System.out.println("    sig : " + signature);
        String vmSig = getVMSignature(signature);
//System.out.println("    vmSig : " + vmSig);
        String vmType = TypeConversion.translateFromCToVMType(myVMReturn);
        if(vmType.compareTo(TypeConversion.FULLY_QUALIFIED_CLASS) == 0 ||
           vmType.compareTo("[" + TypeConversion.FULLY_QUALIFIED_CLASS) == 0) {
//System.out.println("myVMReturn : " + myVMReturn);
            try {
                vmType = vmType.concat(cct[getCClassIndex(myVMReturn)].getJNIName()/*getFullClassname(myVMReturn)*/ + ";");
            }
            catch (ClassNotFoundException ex) { ex.printStackTrace(); }
        }

        String mn;
//System.out.println("METHOD RETURN ->" + methodReturn + "<-");
        if(methodReturn.compareTo("") == 0) mn = "\"<init>\"";
        else mn = "\"" + methodName + "\"";
            
        myLine = myLine.concat(mn + ", \"(" + vmSig + ")" + vmType + "\");");
        return myLine;

    }

    /**
     * 
     * @param returnType
     * @param sigItems
     * @param isStatic
     */
    private void constructAndWriteMethodCall(String returnType, MethodSignatureItem[] sigItems,
                                             boolean isStatic) {
        String myLine;
        // ctor
        if(returnType.compareTo("") == 0) {
            myLine = new String("myObject = (jenv)->NewObject(myClass, " + methodID);

            for(int i = 0; i < sigItems.length; i++) {

//System.out.println("------------------------------------");
//System.out.println("varType : " + sigItems[i].varType);
//System.out.println("varName : " + sigItems[i].varName);
//System.out.println("dimension : " + sigItems[i].arrayDimensions);
//System.out.println("------------------------------------");
                if(sigItems[i].arrayDimensions > 0)
                    createArrayCode(sigItems[i]);

            }
            for(int i = 0; i < sigItems.length; i++) {
                // Handle char *
                if(sigItems[i].varType.compareTo("char *") == 0 &&
                   sigItems[i].arrayDimensions == 0) {
                    myLine = myLine.concat(", (jenv)->NewStringUTF(" + "arg_" + i + ")");
                }
                else {
                	if(sigItems[i].arrayDimensions == 0)
                        myLine = myLine.concat(", " + sigItems[i].varName);
                	else
                		myLine = myLine.concat(", " + sigItems[i].varName + "Array_0");
//System.out.println("pair : " + pairs[i] + "  is basic : " + TypeConversion.isBasicJavaType(pairs[i]));
                    String vType = new String(sigItems[i].varType);
                    while(vType.contains("*")) vType = vType.replace("*", "");
                    if(!TypeConversion.isBasicCType(vType) && sigItems[i].arrayDimensions == 0) {
                        myLine = myLine.concat("->getJavaObject()");
                    }
                }

            }
            myLine = myLine.concat(");");
            writeLine(myLine);
            writeHashCode("myObject");
            myLine = new String(objectPersistHash + "::addEntry(hashValue, this);");
            writeLine(myLine);
            
            // Call superclass setJavaObject
            for(int i = 0; i < cct[classIndex].getExtends().length; i++) {
                writeLine(cct[classIndex].getExtends()[i] + "::setJavaObject(myObject);");
            }
        } // end ctor case
        else {
            if(returnType.compareTo("void") == 0) {
                myLine = new String("(jenv)->" + TypeConversion.getJNIMethodForCType(returnType, isStatic));
            }
            else {
                String nType = TypeConversion.getNativeTypeForCType(returnType);
                writeLine(nType + " returnType;");  
                myLine = new String("returnType = (" + nType + ")(jenv)->" + TypeConversion.getJNIMethodForCType(returnType, isStatic));
            }
            
            if(isStatic) {
                myLine = myLine.concat("(myClass, ");
            }
            else {
                myLine = myLine.concat("(myObject, ");
            }
            myLine = myLine.concat(methodID);
            
//            String[] pairs = StringUtilities.parseCommaSeparatedList(signature);
            for(int i = 0; i < sigItems.length; i++) {
//System.out.println("item len : " + item.length);  
                // Handle char *
                if(sigItems[i].varType.startsWith("char *") &&
                   sigItems[i].arrayDimensions == 0) {
                    myLine = myLine.concat(", (jenv)->NewStringUTF(" + "arg_" + i + ")");
                }
                else {
                    if(sigItems[i].arrayDimensions > 0)
                        this.createArrayCode(sigItems[i]);


                    if(sigItems[i].arrayDimensions == 0)
                        myLine = myLine.concat(", " + sigItems[i].varName);
                    else
                        myLine = myLine.concat(", " + sigItems[i].varName + "Array_0");

                    String vType = new String(sigItems[i].varType);
                    while(vType.contains("*")) vType = vType.replace("*", "");
                    if(!TypeConversion.isBasicCType(vType) &&
                       sigItems[i].arrayDimensions == 0) {
                        myLine = myLine.concat("->getJavaObject()");
                    }
                }

            }
            
            myLine = myLine.concat(");");
            
            writeLine(myLine);
//System.out.println("return type -> " + returnType);
            if(returnType.compareTo("void") != 0) {
                // String is a special case
                if (returnType.compareTo("char *") == 0) {
                    writeLine("jboolean isCopy;");
                    writeLine("const char *cReturn = (jenv)->GetStringUTFChars(returnType, &isCopy);");
                    writeLine("char *cString = (char *) malloc ((strlen(cReturn) + 1) * sizeof(char));");
                    writeLine("strcpy(cString, cReturn);");
                    writeLine("(jenv)->ReleaseStringUTFChars(returnType, cReturn);");
                    myLine = new String("return cString;");
                }
                else if(TypeConversion.isBasicCType(returnType)) {
                    myLine = new String("return ");
//                    myLine = myLine.concat("(" + TypeConversion.getCType(returnType) + ")returnType;");
                  myLine = myLine.concat("(" + returnType + ")returnType;");
                }
                else {
                    writeHashCode("returnType");
                    myLine = new String("void *cObj = " + objectPersistHash + "::getCObject(hashValue);");
                    writeLine(myLine);
                    // If the object is not in the object hash, then the java
                    // object is instantiated, but a C++ object holding the
                    // java object is not instantiated.  Need to instantiate
                    // the C++ object
                    writeLine("if(cObj == NULL) {");

                    indentLevel++;
                    
                    String ret = new String(returnType);
                    // Remove pointer notation
                    ret = ret.replace("*", "");
                    // Remove array notation
                    ret = ret.replace("[]", "");
                    ret = StringUtilities.removeEdgeWhitespace(ret);
                    try {
                        String[] subclass;
                        // get subclass list for return type including the class itself
                        if(cct[getCClassIndex(ret)].isPureVirtualClass() || cct[getCClassIndex(ret)].isAbstractClass()) {
                            subclass = cct[getCClassIndex(ret)].getSubclassList();
                        }
                        else {
                            subclass = new String[cct[getCClassIndex(ret)].getSubclassList().length + 1];
                            subclass[0] = new String(cct[classIndex].getClassname());
                            for(int i = 0; i < cct[getCClassIndex(ret)].getSubclassList().length; i++) {
                                subclass[i+1] = new String(cct[getCClassIndex(ret)].getSubclassList()[i]);
                            }
                        }
                        boolean first = true;
                        for(int i = 0; i < subclass.length; i++) {
    
                            if(jct[getCClassIndex(subclass[i])].isAbstractClass() ||
                               jct[getCClassIndex(subclass[i])].isInterface()) continue;
    
                            if(first) {
                                myLine = "if (";
                                first = false;
                            }
                            else myLine = "else if (";
                            
                            myLine = myLine.concat("(jenv)->IsInstanceOf(returnType, (jenv)->FindClass(\"" + cct[getCClassIndex(subclass[i])].getJNIName()/*getFullClassname(subclass[i])*/ + "\")) == JNI_TRUE) {");
                            writeLine(myLine);
    
                            indentLevel++;
                            myLine = new String("cObj = new " + subclass[i] + "(returnType);");
                            writeLine(myLine);
                            indentLevel--;
                            
                            writeLine("}");
    
                        }
                    }
                    catch (ClassNotFoundException ex) { 
                        System.out.println("Treating class like it is an inner class.");
                    }
                    // get subclasses of the return type

                    // add return type in case it is concrete
                    
                    indentLevel--;
                    writeLine("}");
                    
                    myLine = new String("return (" + returnType + ")(cObj);");
                }
                writeLine(myLine);
            }

        } // end non-ctor method

    }
    
    /**
     * 
     * @param signature The signature of the C method
     * @return Returns the VM signature required to get the Java method ID
     *         as a string.
     */
    private String getVMSignature(String signature) {
//System.out.println("signature : " + signature);
        String vm = new String("");
        String[] pairs = StringUtilities.parseCommaSeparatedList(signature);
        for(int i = 0; i < pairs.length; i++) {
            pairs[i] = StringUtilities.removeEdgeWhitespace(pairs[i]);
//System.out.println("    pair -> " + pairs[i]);
            String type = TypeConversion.translateFromCToVMType(pairs[i]);
            String nonArrayType = new String(type);
            nonArrayType = nonArrayType.replace("[", "");
            if(nonArrayType.compareTo(TypeConversion.FULLY_QUALIFIED_CLASS) == 0) {
                try {
                    type = type.concat(cct[getCClassIndex(pairs[i])].getJNIName() + ";");
                }
                catch (ClassNotFoundException ex) { ex.printStackTrace(); }
            }
//System.out.println("      type -> " + type);

            vm = vm.concat(type);
        }
        return vm;
    }
    
    /**
     * 
     * @param cn Classname to get full class of
     * @return
     */
    private String getFullClassname(String cn) {
        // Remove any pointer notation from classname
        cn = cn.replace("*", "");
        // Replace array notation
        cn = cn.replace("[]", "");
        cn = StringUtilities.removeEdgeWhitespace(cn);
//System.out.println("    cn = " + cn);
        String fullName = new String("UNKNOWN_CLASS");
        for(int i = 0; i < jct.length; i++) {
            if(cn.compareTo(jct[i].getClassname()) == 0) {
                if(jct[i].getPackageName().compareTo("") == 0)
                    fullName = new String(jct[i].getClassname());
                else
                    fullName = new String(jct[i].getPackageName() + "/" + jct[i].getClassname());
            }
        }
        while(fullName.contains(".")) fullName = fullName.replace(".", "/");
//System.out.println("        FULLNAME -> " + fullName);
        return fullName;
    }
    
    /**
     * Write the code to the C file that gets a created JVM and attaches the
     * current thread to the JVM.
     * @param packageName
     */
    private void writeGetJVM(String packageName) {
        writeLine("JavaVM *jvm;");
        writeLine("jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, NULL);");
        writeLine("JNIEnv *jenv;");
        writeLine("(jvm)->AttachCurrentThread((void **)&jenv, NULL);");
    }
    
    private void writeHashCode(String jObj) {
        String hashLine = this.constructMethodID("hashCode", "int", "", "hashID", false);
        writeLine(hashLine);
        writeLine("jint hashValue = (jenv)->CallIntMethod(" + jObj + ", hashID);");
    }
    
    private int getCClassIndex(String classname) throws ClassNotFoundException {

        classname = classname.replace("[]", "");
        classname = classname.replace("*", "");
        classname = StringUtilities.removeEdgeWhitespace(classname);
        for(int i = 0; i < cct.length; i++) {
            if(classname.compareTo(cct[i].getClassname()) == 0) return i;
        }
        throw new ClassNotFoundException("Required class does not appear to be in the input file : " + classname);

    }
    
    private void createArrayCode(MethodSignatureItem item) {
//System.out.println("ARRAY DIMENSIONS = " + item.arrayDimensions);
        if(item.arrayDimensions > 0) {
            String arrayString = new String("");

            for(int j = 0; j < item.arrayDimensions; j++) {
                String arrayClass = null;
                if(!TypeConversion.isBasicCType(item.varType) ||
                   item.varType.startsWith("char *")) {
                    arrayClass = new String(item.varName + "Class");
                    String arrayClassLine = new String("jclass " + arrayClass + " = (jenv)->FindClass(\"");
                    if(item.varType.startsWith("char *")) {
                        arrayClassLine = arrayClassLine.concat(String.class.getName().replace(".", "/") + "\");");                        
                    }
                    else {
                        try {
                            arrayClassLine = arrayClassLine.concat(cct[getCClassIndex(item.varType)].getJNIName() + "\");");
                        }
                        catch (ClassNotFoundException ex) { ex.printStackTrace();}
                    }
                    writeLine(arrayClassLine);
                }
                String arrayName = new String(item.varName + "Array_" + j);
                arrayString = arrayString.concat(TypeConversion.getArrayTypeForCType(item.varType));
                arrayString =
                    arrayString.concat(" " + arrayName);
                arrayString =
                    arrayString.concat(" = (jenv)->");
                arrayString = arrayString.concat(TypeConversion.getArrayMethodForCType(item.varType));
                arrayString = arrayString.concat("(" + item.arrayArg[j]);
                
                // Arguments to create array are different for an Object and a native type
                if(TypeConversion.isBasicCType(item.varType) &&
                   item.varType.compareTo("char *") != 0)
                    arrayString = arrayString.concat(");");
                else
                    arrayString = arrayString.concat(", " + arrayClass + ", NULL);");
                
                writeLine(arrayString);
                
                // Algorithm to populate is different for an Object and native type
                if(TypeConversion.isBasicCType(item.varType) &&
                   item.varType.compareTo("char *") != 0) {
                    writeLine("(jenv)->" + TypeConversion.getArrayFillForCType(item.varType) +
                              "(" + arrayName + ", 0, " + item.arrayArg[j] + ", (" + TypeConversion.getNativeTypeForCType(item.varType)+ "*)" + item.varName + ");");
                }
                else {
                    String idxString = new String(item.arrayArg[j] + "_idx");
                    arrayString = new String("for(int " + idxString + "=0; " + idxString + " < " + item.arrayArg[j] + "; " + idxString + "++) {");
                    writeLine(arrayString);
                    indentLevel++;
                    arrayString = new String("(jenv)->SetObjectArrayElement(" + arrayName + ",");
                    arrayString = arrayString.concat(" " + idxString + ", ");
                    
                    if(item.varType.startsWith("char *")) {
                        arrayString = arrayString.concat("(jenv)->NewStringUTF(" + item.varName + "[" + idxString + "])");
                        arrayString = arrayString.concat(");");
                    }
                    else {
                        arrayString = arrayString.concat(item.varName + "[" + idxString + "]");
                        arrayString = arrayString.concat("->getJavaObject());");
                    }
                    writeLine(arrayString);
                    indentLevel--;
                    writeLine("}");
                }
                
            }
        }
    }

}
