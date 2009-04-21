package javaToC;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javaToC.SignatureUtilities.MethodSignatureItem;


public class IncludeFileGenerator extends FileGenerator {

    private ClassTypeC cct;
    private InputParameters inputParms;
    private ImportResolver importResolver;
    
    IncludeFileGenerator(File includeFile, ClassTypeC cc, InputParameters ip, ImportResolver ir) {

        cct = cc;
        inputParms = ip;
        importResolver = ir;
        indentLevel = 0;
        
        try {
            writer = new BufferedWriter(new FileWriter(includeFile));
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    public void writeIncludeFile() {
    	try {
    		
    		// ifndef/define statement
    	    writer.newLine();
    	    writeLine("#ifndef " + cct.getClassname() + "GLUE_WRAPPER_H");
    	    writeLine("#define " + cct.getClassname() + "GLUE_WRAPPER_H");
    	    writer.newLine();
    	    
    	    addIncludes();
    	    
    	    if(inputParms.useNamespace()) {
    	        writer.newLine();
    	        writeLine("namespace " + cct.getNamespace() + " {");
                indentLevel++;
    	    }

    	    // Class Declaration
            writer.newLine();

            addForwardDeclarations();
            
            writer.newLine();
            
            writeClass(cct);
            indentLevel--;
                   
            if(inputParms.useNamespace()) {
                writer.newLine();
                writeLine("} // End namespace");
                indentLevel--;
            }
            
    	    // endif statement
    	    writer.write("#endif"); writer.newLine();
    	    writer.flush();

    	}
    	catch (IOException ex) {
    		ex.printStackTrace();
    	}
    }

    private void addIncludes() {
        
        writeLine("#include \"jni.h\"");
        
        ArrayList<String> myList = importResolver.getIncludeFileList();
        for(int i = 0; i < myList.size(); i++) {
            writeLine("#include \"" + myList.get(i) + ".h\"");
        }
        
    }
    
    private void addForwardDeclarations() {
        // Need to forward declare classes that will be included
        // from the source file
        ArrayList<String> myList = importResolver.getSourceFileList();
        for(int i = 0; i < myList.size(); i++)
            writeLine("class " + myList.get(i) + ";");

    }
    
    private void writeClass(ClassTypeC cct) {
        writeClass(cct, "");
    }
    
    private void writeClass(ClassTypeC cct, String innerClass) {
        try {
            String classLine;
            if(innerClass.compareTo("") == 0)
                classLine = new String("class " + cct.getClassname());
            else
                classLine = new String("class " + innerClass + "::" + cct.getClassname());
            

            classLine = classLine.concat(" : ");
            // concrete inheritance
            if(cct.getExtends().length > 0) {
                for(int i = 0; i < cct.getExtends().length; i++) {
                    if(i > 0) classLine = classLine.concat(",");
                    classLine = classLine.concat(" public "+ cct.getExtends()[i]);
                }
            }
            else {
                classLine = classLine.concat(" public virtual Object");
            }
            // virtual inheritance
            if(cct.getImplements().length > 0) {
                for(int i = 0; i < cct.getImplements().length; i++) {
                    classLine = classLine.concat(",");
                    classLine = classLine.concat(" public virtual "+ cct.getImplements()[i]);
                }
            }

    
            classLine = classLine.concat(" {");
            writeLine(classLine);
            
            indentLevel++;
            
            writer.newLine();

            boolean hasDefaultCtor = false;
            
            // public methods
            if(cct.getMethodName().length > 0 || cct.getNumberOfCtors() > 0 ||
               !cct.isPureVirtualClass()) {
                writer.newLine();
                writeLine("public:");
                writer.newLine();
                indentLevel++;
                
                if(cct.isPureVirtualClass() == false) {
                    // Create ctor(jobject)
                    writeLine(cct.getClassname() + "(jobject jobj);");
                
                    // Ctor
                    for(int i = 0; i < cct.getNumberOfCtors(); i++) {
                        MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(cct.getCtorSignature()[i]);

                        writeLine(cct.getClassname() + "(" + SignatureUtilities.getSignature(mySigItems) + ");");
                        if(cct.getCtorSignature()[i].compareTo("") == 0) hasDefaultCtor = true;
                    }
    
                }
                // Methods
                for(int i = 0; i < cct.getMethodName().length; i++) {
    
                    if(cct.getMethodReturn()[i].compareTo("") != 0) {
                        String mn;
                        if(!cct.getMethodVirtual()[i]) mn = new String("");
                        else mn = new String("virtual"); 
    
                        if(cct.getStatic()[i]) {
//System.out.println(cct.getMethodName()[i] + "(" + cct.getMethodSignature()[i]+")");
                            mn = mn.concat("static");
                        }
    //                  if(cct.getFinal()[i]) {
    //                      if(mn.length() > 0) mn = mn.concat(" ");
    //                      mn = mn.concat("const");
    //                  }
                        if(mn.length() > 0) mn = mn.concat(" ");
                        mn = mn.concat(cct.getMethodReturn()[i]);
                        MethodSignatureItem[] mySigItems = SignatureUtilities.parseMethodSignature(cct.getMethodSignature()[i]);

                        mn = mn.concat(" " + cct.getMethodName()[i] + "(" + SignatureUtilities.getSignature(mySigItems) + ")");
    
                        if(!cct.getMethodVirtual()[i]) 
                            mn = mn.concat(";");
                        else
                            mn = mn.concat(" = 0;");
                        
                        writeLine(mn);
                            
                    }

                }
                                
                indentLevel--;
                
            }

            if(!cct.isPureVirtualClass()) {
                writer.newLine();
                writeLine("protected:");
                indentLevel++;
                if(!hasDefaultCtor)
                    writeLine(cct.getClassname() + "() { }");
                indentLevel--;
            }

            indentLevel--;
        
            writer.newLine();
            writeLine("}; // End class " + cct.getClassname());
/*            
            // Inner Classes
            for(int i = 0; i < cct.getInnerClasses().length; i++) {
                // Need to write access
                writer.newLine();
//                writeLine(cct.getInnerClassAccess()[i] + " :");
//                indentLevel++;
//System.out.println("IL -> " + indentLevel);
                writeClass((ClassTypeC)cct.getInnerClasses()[i], cct.getClassname());
//                indentLevel--;
//                 writeLine("Inner class " + cct.getInnerClasses()[i].getClassname());
            }
*/
//            indentLevel--;
        }
        catch (IOException ex) { ex.printStackTrace(); }
    }
    
    protected void finalize() {
        try {
            writer.close();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
