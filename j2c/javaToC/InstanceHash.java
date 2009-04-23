package javaToC;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class InstanceHash extends FileGenerator {

    String outputDir;
    String className;
    ClassTypeContainer container;

    
    public InstanceHash(String dir, ClassTypeContainer ctc) {
        outputDir = new String(dir);
        className = new String("InstanceHash");
        container = ctc;
    }
  
    /**
     * 
     */
    public void createClass() {
        createInclude();
        createSource();
    }
    
    /**
     * 
     */
    private void createInclude() {
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir +
                    File.separator + className + ".h")));
        
            writeLine("#ifndef " + className + "_WRAPPER_OBJECT_HASH");
            writeLine("#define " + className + "_WRAPPER_OBJECT_HASH");
            writer.newLine();
            
            // Include section
            writeLine("#include \"jni.h\"");
            writeLine("#include \"string.h\"");
            writeLine("#include \"WrapperObject.h\"");
            writer.newLine();
            
            // Class Declaration
            writeLine("class " + className + " {");
            writer.newLine();
            
            indentLevel++;
            
            // PublicSection
            writeLine("public:");
            writer.newLine();
            
            indentLevel++;

            writeLine("static WrapperObject *getInstance(JNIEnv *, jobject);");

            writer.newLine();
            
            indentLevel--;
            
            indentLevel--;
            
            writeLine("};");
            
            writeLine("#endif");
        
            writer.close();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    /**
     * 
     */
    private void createSource() {
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir +
                    File.separator + className + ".cpp")));
            
            writeLine("#include \"" + className + ".h\"");

            for(int i = 0; i < container.getCClassCount(); i++) {
                if(container.getCClass(i).isAbstractClass() == false)
                    writeLine("#include \"" + container.getCClass(i).getClassname() + ".h\"");
            }
            writer.newLine();
            
            String[] namespace = getNamespaceList();
            for(int i = 0; i < namespace.length; i++) {
                writeLine("using namespace " + namespace[i] + ";");
            }
            
            writer.newLine();
            writeLine("WrapperObject *" + className + "::getInstance(JNIEnv *jenv, jobject myObject) {");
            indentLevel++;

            writeLine("jclass objectClass = (jenv)->GetObjectClass(myObject);");
            writeLine("jmethodID getClassID = (jenv)->GetMethodID(objectClass, \"getClass\", \"()Ljava/lang/Class;\");");
            writeLine("jobject classObject = (jenv)->CallObjectMethod(objectClass, getClassID);");

            writeLine("jclass classClass = (jenv)->GetObjectClass(classObject);");
            writeLine("jmethodID getNameID = (jenv)->GetMethodID(classClass, \"getName\", \"()Ljava/lang/String;\");");
            writeLine("jobject nameObject = (jenv)->CallObjectMethod(objectClass, getNameID);");

            writeLine("jboolean isCopy;");
            writeLine("const char *classString = (jenv)->GetStringUTFChars((jstring)nameObject, &isCopy);");
            
            writeLine("printf(\"CLASS STRING : %s\\n\", classString); fflush(stdout);");
            writer.newLine();
            
            writeLine("WrapperObject *returnObject = NULL;");
            
            boolean init = true;
            for(int i = 0; i < container.getCClassCount(); i++) {
                String compareLine = new String("");
                if(container.getCClass(i).isAbstractClass() == false) {
                    if(init) {
                        compareLine = compareLine.concat("if(");
                        init = false;
                    }
                    else {
                        compareLine = compareLine.concat("else if(");
                    }
                    
                    compareLine = compareLine.concat("strcmp(classString, \"");
                    compareLine = compareLine.concat(container.getJavaClass(i).getJNIName().replace("/", ".") + "\") == 0)");
                    compareLine = compareLine.concat(" {");
                    
                    writeLine(compareLine);
                    indentLevel++;
                    
                    writeLine("returnObject = new " + container.getCClass(i).getClassname() + "(myObject);");
                    indentLevel--;
                    
                    writeLine("}");
                }

            }
            writeLine("else {");
            indentLevel++;
            
            writeLine("returnObject = new WrapperObject(myObject);");
            indentLevel--;
            
            writeLine("}");
            writer.newLine();
            
            writeLine("(jenv)->ReleaseStringUTFChars((jstring)nameObject, classString);");
            writer.newLine();
            
            writeLine("return returnObject;");

            indentLevel--;
            
            writeLine("}");
            
            writer.close();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
    
    /**
     * 
     * @return
     */
    private String[] getNamespaceList() {
        String[] namespace;
        
        ArrayList<String>nList = new ArrayList<String>();
        for(int i = 0; i < container.getCClassCount(); i++) {
            boolean inList = false;
            for(int j = 0; j < nList.size(); j++) {
                System.out.println("namespace : " + container.getCClass(i).getNamespace());
                if(container.getCClass(i).getNamespace().compareTo(nList.get(j)) == 0) {
                    inList = true;
                    break;
                }
            }
            if(!inList) {
                nList.add(container.getCClass(i).getNamespace());
            }
        }
        
        namespace = new String[nList.size()];
        for(int i = 0; i < nList.size(); i++) {
            namespace[i] = nList.get(i);
        }
        
        return namespace;
    }
    
}
