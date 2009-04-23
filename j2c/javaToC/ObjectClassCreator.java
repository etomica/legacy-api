package javaToC;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ObjectClassCreator extends FileGenerator {
    
    private String outputDir;
    private String interfaceName;
    private String concreteName;
    private CSourceGenerationUtilities cUtils;
    
    public ObjectClassCreator(String dir, ClassTypeContainer container) {
        outputDir = dir;
        interfaceName = new String("IWrapperObject");
        concreteName = new String("WrapperObject");
        cUtils = new CSourceGenerationUtilities("myMethodID", container);
    }
    
    /**
     * 
     */
    public void createInterface() {
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir +
                    File.separator + interfaceName + ".h")));
        
            writeLine("#ifndef " + interfaceName + "_WRAPPER_OBJECT_HASH");
            writeLine("#define " + interfaceName + "_WRAPPER_OBJECT_HASH");
            writer.newLine();
            
            // Include section
            writeLine("#include \"jni.h\"");
            writer.newLine();
            
            // Class Declaration
            writeLine("class " + interfaceName + " {");
            writer.newLine();
            
            indentLevel++;
            
            // PublicSection
            writeLine("public:");
            writer.newLine();
            
            indentLevel++;

            writeLine("virtual jobject getJavaObject() = 0;");
            writer.newLine();
            
            indentLevel--;
            
            // Private section
            writeLine("protected:");
            writer.newLine();
            
            indentLevel++;
            
            writeLine("jobject myObject;");
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
    public void createConcreteClass() {
        createConcreteInclude();
        createConcreteSource();
    }
    
    /**
     * 
     */
    private void createConcreteInclude() {
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir +
                    File.separator + concreteName + ".h")));
        
            writeLine("#ifndef " + concreteName + "_WRAPPER_OBJECT_HASH");
            writeLine("#define " + concreteName + "_WRAPPER_OBJECT_HASH");
            writer.newLine();
            
            // Include section
            writeLine("#include \"jni.h\"");
            writeLine("#include \"" + interfaceName + ".h\"");
            writer.newLine();
            
            // Class Declaration
            writeLine("class " + concreteName + " : public virtual " + interfaceName + " {");
            writer.newLine();
            
            indentLevel++;
            
            // PublicSection
            writeLine("public:");
            writer.newLine();
            
            indentLevel++;
    
            writeLine(concreteName + "(jobject jobj);");
            writeLine("jobject getJavaObject() { return myObject; };");
            writer.newLine();
            
            indentLevel--;
            
            // Protected Section
            writeLine("protected:");
            writer.newLine();
            
            indentLevel++;
    
            writeLine(concreteName + "();");
            writeLine("void setJavaObject(jobject jobj) {myObject = jobj;};");
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
    private void createConcreteSource() {
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir +
                    File.separator + concreteName + ".cpp")));
            writeLine("#include <typeinfo>");
            writeLine("#include \"" + concreteName + ".h\"");
            writeLine("#include \"ObjectPersist.h\"");
            writer.newLine();
            
            writeLine(concreteName + "::" + concreteName + "() {");
            writeLine("}");
            writer.newLine();
            
            writeLine(concreteName + "::" + concreteName + "(jobject jobj) {");
            indentLevel++;
            writeLine("myObject = jobj;");
            writeLine("if(typeid(*this) == typeid(" + concreteName + ")) {");
            
            indentLevel++;

            writeLine("JavaVM *jvm;");
            writeLine("jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, NULL);");
            writeLine("JNIEnv *jenv;");
            writeLine("(jvm)->AttachCurrentThread((void **)&jenv, NULL);");

            writeLine("jclass myClass = (jenv)->GetObjectClass(myObject);");

            String hashLine = cUtils.constructMethodID("hashCode", "int", "", "hashID", false);
            
            writeLine(hashLine);
            writeLine("jint hashValue = (jenv)->CallIntMethod(myObject, hashID);");
            
            writeLine("ObjectPersist::addEntry(hashValue, this);");
            
            indentLevel--; 
            writeLine("}");
            
            indentLevel--;
            writeLine("}");
            
            writer.close();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
