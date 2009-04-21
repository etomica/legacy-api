package javaToC;
import java.io.BufferedWriter;
import java.io.IOException;


public class FileGenerator {

    public static final String INDENT = "  ";
    protected BufferedWriter writer;
    protected int indentLevel;
    
    protected void writeLine(String line) {
        try {
        for(int i = 0; i < indentLevel; i++) writer.write(INDENT);
        writer.write(line);
        writer.newLine();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
