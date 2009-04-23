package javaToC;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javaToC.SignatureUtilities.MethodSignatureItem;


public class CFileGenerator extends FileGenerator {

    private ArrayList<String> includeList;
    private ClassTypeContainer container;
    private InputParameters inputParms;
    private String objectPersistHash;
    private String methodID = new String("myMethodID");
    private ImportResolver importResolver;
    private CSourceGenerationUtilities cUtils;
    private ClassTypeC myCClass;
    private ClassTypeJava myJavaClass;

    
    CFileGenerator(File includeFile, ClassTypeContainer ctc, int idx, InputParameters ip,
                   String op, ImportResolver ir) {

        container = ctc;
        inputParms = ip;
        importResolver = ir;
        indentLevel = 0;
        objectPersistHash = op;
        myCClass = container.getCClass(idx);
        myJavaClass = container.getJavaClass(idx);

        try {
            writer = new BufferedWriter(new FileWriter(includeFile));
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
        
        cUtils = new CSourceGenerationUtilities(methodID, container);
    }
    
    /**
     * 
     */
    public void writeCFile() {
        
        String packageName = new String(myJavaClass.getPackageName());
        while(packageName.contains(".")) packageName = packageName.replace(".", "/");

        try {
            boolean returningCharPointer = false;
        	for(int i = 0; i < myCClass.getMethodReturn().length; i++) {
        		if(myCClass.getMethodReturn()[i].compareTo("char *") == 0) {
        			returningCharPointer = true;
        			break;
        		}
        	}
        	
        	if(returningCharPointer) {
        		writeLine("#include \"string.h\"");
        		writeLine("#include \"malloc.h\"");        		
        	}
            writeLine("#include <typeinfo>");
writeLine("#include \"InstanceHash.h\"");
        	for(int i = 0; i < importResolver.getSourceFileList().size(); i++) {
        	    writeLine("#include \"" + importResolver.getSourceFileList().get(i) + ".h\"");
        	}
        	
            includeList = new ArrayList<String>();
            includeList.add(myCClass.getClassname());
            includeList.add(objectPersistHash);
/*
            // for each return type, include all subclasses
            for(int i = 0; i < myCClass.getMethodReturn().length; i++) {
                String ret = new String(myCClass.getMethodReturn()[i]);
                // Remove pointer notation
                ret = ret.replace("*", "");
                // Remove array notation
                ret = ret.replace("[]", "");
                ret = StringUtilities.removeEdgeWhitespace(ret);
//System.out.println("ret ->" + ret + "<-");
                if(!TypeConversion.isBasicCType(ret) && ret.compareTo("") != 0) {
                    try {
                        int retIdx = container.getCClassIndex(ret);
//System.out.println("idx = " + retIdx);
                        for(int j = 0; j < container.getCClass(retIdx).getSubclassList().length; j++) {
//System.out.println("  possible : " + cct[retIdx].getSubclassList()[j]);
                            boolean addInclude = true;
                            for(int k = 0; k < includeList.size(); k++) {
                                if(container.getCClass(retIdx).getSubclassList()[j].compareTo((String)includeList.get(k)) == 0) {
                                    addInclude = false;
                                    break;
                                }
                            }
                            if(addInclude) includeList.add(container.getCClass(retIdx).getSubclassList()[j]);
                        }
                    }
                    catch (ClassNotFoundException ex) {
                        System.out.println("Treating class like it is an inner class.");
                        //ex.printStackTrace();
                    }
                }
            }
*/
            for(int i = 0; i < includeList.size(); i++) {
                writeLine("#include \"" + (String)includeList.get(i) + ".h\"");
            }
            
            if(inputParms.useNamespace()) {
                writer.newLine();
                writeLine("namespace " + myCClass.getNamespace() + " {");
                writer.newLine();
                indentLevel++;
            }
            
            if(!myCClass.isPureVirtualClass()) {
                
                // create ctor(jobject)
                String ctorDeclare;
                ctorDeclare = new String(myCClass.getClassname() + "::" + myCClass.getClassname() + "(jobject jobj)");

//                if(myCClass.getExtends().length == 0)
//                    ctorDeclare = ctorDeclare.concat(" : WrapperObject(jobj) {");
                if(myCClass.getExtends().length > 0)/*else*/ {
                    for(int i = 0; i < myCClass.getExtends().length; i++) {
                        ctorDeclare = ctorDeclare.concat(" : " + myCClass.getExtends()[i] + "(jobj)");
                    }

                }
                ctorDeclare = ctorDeclare.concat(" {");
                
                writeLine(ctorDeclare);
                indentLevel++;
                
//                writeLine("myObject = jobj;");
                writeLine("if(typeid(*this) == typeid(" + myCClass.getClassname() + ")) {");
                indentLevel++;
                
                writeLine("setJavaObject(jobj);");
                
                writeGetJVM();

                writeLine("jclass myClass = (jenv)->FindClass(\"" + myCClass.getJNIName() + "\");");
                writeHashCode("myObject");
                
                writeLine(objectPersistHash + "::addEntry(hashValue, this);");
                
                indentLevel--; 
                writeLine("}");
                
                indentLevel--;
                writeLine("}");
                writer.newLine();

                // Ctors
                for(int i = 0; i < myCClass.getNumberOfCtors(); i++) {
                    String methodDeclare = myCClass.getClassname() + "::" + myCClass.getClassname() + "(";
                    MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(myCClass.getCtorSignature()[i]);
                    methodDeclare = methodDeclare.concat(SignatureUtilities.getSignature(mySigItems));
                    methodDeclare = methodDeclare.concat(") {");

                    writeLine(methodDeclare);
                    
                    indentLevel++;
                    
    
                    writeLine("if(typeid(*this) == typeid(" + myCClass.getClassname() + ")) {");
                    indentLevel++;
                    
                    writeGetJVM();
                    
                    writeLine("jclass myClass = (jenv)->FindClass(\"" + myCClass.getJNIName() + "\");");
//System.out.println("CTOR : " + cct[classIndex].getCtorSignature()[i]);
                    writeLine(cUtils.constructMethodID(myCClass.getClassname(), "", myCClass.getCtorSignature()[i], false));
                    constructAndWriteMethodCall("", mySigItems, false);
    
                    indentLevel--; 
                    writeLine("}");
                    
                    indentLevel--;
    
                    writeLine("}");
                    writer.newLine();
                }

            }
            
            // public methods
            // It is possible that the class does not have a public ctor.
            // In that case, would need to add one for creation of myObject
            // and inclusion in proxy hash?
            if(myCClass.getMethodName().length > 0) {
                for(int i = 0; i < myCClass.getMethodName().length; i++) {

                    String methodDeclare = myCClass.getMethodReturn()[i] + " " +
                    myCClass.getClassname() + "::" +
                    myCClass.getMethodName()[i] + "(";
                    MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(myCClass.getMethodSignature()[i]);
                    methodDeclare = methodDeclare.concat(SignatureUtilities.getSignature(mySigItems));

                    methodDeclare = methodDeclare.concat(") {");
                    
                    writeLine(methodDeclare);
                    writer.newLine();
                    
                    indentLevel++;
                    
                    writeGetJVM();
                    
                    writeLine("jclass myClass = (jenv)->FindClass(\"" + myCClass.getJNIName() + "\");");
                    writeLine(cUtils.constructMethodID(myCClass.getMethodName()[i],
                            myCClass.getMethodReturn()[i],
                            myCClass.getMethodSignature()[i],
                            myCClass.getStatic()[i]));
//System.out.println("Method Return : " + myCClass.getMethodReturn()[i]);
                    constructAndWriteMethodCall(myCClass.getMethodReturn()[i],
                                                mySigItems,
                                                myCClass.getStatic()[i]);

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
                    myLine = new String("WrapperObject *cObj = " + objectPersistHash + "::getCObject(hashValue);");
                    writeLine(myLine);
                    // If the object is not in the object hash, then the java
                    // object is instantiated, but a C++ object holding the
                    // java object is not instantiated.  Need to instantiate
                    // the C++ object
                    writeLine("if(cObj == NULL) {");
                    indentLevel++;

                    writeLine("cObj = InstanceHash::getInstance(jenv, returnType);");
                    indentLevel--;
                    writeLine("}");
                    
                    myLine = new String("return dynamic_cast<" + returnType + ">(cObj);");
                }
                writeLine(myLine);
            }

        } // end non-ctor method

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
        
        for(int i = 0; i < container.getJavaClassCount(); i++) {
            ClassTypeJava jct = container.getJavaClass(i);
            if(cn.compareTo(jct.getClassname()) == 0) {
                if(jct.getPackageName().compareTo("") == 0)
                    fullName = new String(jct.getClassname());
                else
                    fullName = new String(jct.getPackageName() + "/" + jct.getClassname());
            }
        }
        while(fullName.contains(".")) fullName = fullName.replace(".", "/");
//System.out.println("        FULLNAME -> " + fullName);
        return fullName;
    }
    

    
    private void writeHashCode(String jObj) {
        String hashLine = cUtils.constructMethodID("hashCode", "int", "", "hashID", false);
        writeLine(hashLine);
        writeLine("jint hashValue = (jenv)->CallIntMethod(" + jObj + ", hashID);");
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
                            arrayClassLine = arrayClassLine.concat(container.getCClass(item.varType).getJNIName() + "\");");
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

    /**
     * Write the code to the C file that gets a created JVM and attaches the
     * current thread to the JVM.
     */
    private void writeGetJVM() {
        writeLine("JavaVM *jvm;");
        writeLine("jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, NULL);");
        writeLine("JNIEnv *jenv;");
        writeLine("(jvm)->AttachCurrentThread((void **)&jenv, NULL);");
    }
}
