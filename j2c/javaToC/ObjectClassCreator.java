package javaToC;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ObjectClassCreator extends FileGenerator {
    
    private String outputDir;
    private String interfaceName;
    private String concreteName;
    
    public ObjectClassCreator(String dir) {
        outputDir = dir;
        interfaceName = new String("IObject");
        concreteName = new String("Object");
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
    
            writeLine("virtual jobject getJavaObject() { return myObject; };");
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

    }
}
