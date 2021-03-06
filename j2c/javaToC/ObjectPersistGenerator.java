package javaToC;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class ObjectPersistGenerator extends FileGenerator {

    private String className;
    private String outputDir;
    
    ObjectPersistGenerator(String name, String dir) {
        className = name;
        outputDir = dir;
    }
    
    void createIncludeFile() {
    
        try {
            writer = new BufferedWriter(new FileWriter(new File(outputDir + File.separator + className + ".h")));
        
            writeLine("#ifndef " + className + "_WRAPPER_OBJECT_HASH");
            writeLine("#define " + className + "_WRAPPER_OBJECT_HASH");
            writer.newLine();
            
            // Include section
            writeLine("#include \"jni.h\"");
            writeLine("#include <map>");
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

            writeLine("static WrapperObject *getCObject(jint hashCode);");
            writeLine("static void addEntry(jint hashCode, WrapperObject *cObj);");
            writer.newLine();
            
            indentLevel--;
            
            // Private section
            writeLine("private:");
            writer.newLine();
            
            indentLevel++;
            
            writeLine("static std::map<jint, WrapperObject *> objectHash;");
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
    
    void createCFile() {
        
        try {  
            writer = new BufferedWriter(new FileWriter(new File(outputDir + File.separator + className + ".cpp")));
            
            writeLine("#include \"" + className + ".h\"");
            writer.newLine();
            
            writeLine("std::map<jint, WrapperObject *>ObjectPersist::objectHash;");
            writer.newLine();
            
            writeLine("void " + className + "::addEntry(jint hashCode, WrapperObject *cObj) {");
            
            indentLevel++;
            writeLine("if(objectHash.find(hashCode) == objectHash.end()) {");
            indentLevel++;
            writeLine("objectHash.insert(std::pair<jint, WrapperObject *>(hashCode, cObj));");
writeLine("//printf(\"----------- ADD %d -------------->  %x\\n\", hashCode, cObj); fflush(stdout);");
            indentLevel--;
            writeLine("}");
            indentLevel--;
            
            writeLine("}");
            writer.newLine();
            
            writeLine("WrapperObject *" + className + "::getCObject(jint hashCode) {");
            
            indentLevel++;
            writeLine("WrapperObject *theObj = NULL;");
            writeLine("if(objectHash.find(hashCode) != objectHash.end()) theObj = objectHash.find(hashCode)->second;");
writeLine("//printf(\"---------------FETCH %d ---------->  %x\\n\", hashCode, theObj); fflush(stdout);");
            writeLine("return theObj;");
            
            indentLevel--;
            
            writeLine("}");
            writer.newLine();

            writer.close();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
        
    }
}
