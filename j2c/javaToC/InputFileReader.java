package javaToC;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class InputFileReader {

    private String inputFile;
//    private ArrayList includeDirs;
    private ArrayList classList;
    private InputParameters inputParms;
    private String[] files;
    private String outputDir;
    
    InputFileReader(String[] args) {

        inputParms = new InputParameters();

//        includeDirs = new ArrayList();
//        includeDirs.add(".");
        classList = new ArrayList();
        outputDir = new String(".");

        
        inputFile = new String(args[args.length-1]);
        for(int i = 0; i < args.length-1; i++) {
 
            // Include directory
//            if(args[i].contains("-I") && args[i].indexOf("-I") == 0) {
//                includeDirs.add(args[i].substring("-I".length()));
//            }

            // Namespace name
            if(args[i].contains("-N") && args[i].indexOf("-N") == 0) {
                inputParms.setNamespace(new String(args[i].substring("-N".length())));
            }
            
            // use namespace directive
            if(args[i].contains("-np") && args[i].indexOf("-np") == 0) {
                inputParms.setUsePackageAsNamespace(true);
                inputParms.setUseNamespace(true);
            }
            else if(args[i].contains("-n") && args[i].indexOf("-n") == 0) {
                inputParms.setUseNamespace(true);
            }
            
            // Output directory
            if(args[i].contains("-O") && args[i].indexOf("-O") == 0) {
                outputDir = args[i].substring("-O".length());
            }
            
            // Forward Declaration of used classes
            if(args[i].contains("-f") && args[i].indexOf("-f") == 0) {
                inputParms.setForwardDeclare(true);
            }
        }
        
        try {
            BufferedReader reader = new BufferedReader(new FileReader(new File(inputFile)));
            String line;
            while((line = reader.readLine()) != null) {
                line = StringUtilities.removeEdgeWhitespace(line);
                if(line.compareTo("") != 0 && line.startsWith("#") == false) {
                    classList.add(line);
                }
            }
            reader.close();
        }
        catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
        
        files = new String[classList.size()];
        for(int i = 0; i < classList.size(); i++) {
            files[i] = new String((String)classList.get(i));
        }
        
    }
    
    public InputParameters getParameters() {
        return inputParms;
    }
    
    public String[] getFileList() {
        return files;
    }
    
    public String getOutputDir() {
        return outputDir;
    }
    
    public static void printUsage() {
        System.out.println("Usage :");
        System.out.println("  jtoc <OPTIONS> <INPUT FILE>");
        System.out.println("    -n       : Use namespaces (see also -N option)");
        System.out.println("    -f       : User forward declarations in generated include files");
        System.out.println("    -np      : Use java package name as namespaces");
//        System.out.println("    -I<DIR>  : Directory entry to look for java files");
        System.out.println("    -N<NAME> : Name of namespace for -n option");
        System.out.println("    -O<DIR>  : Name of directory to write output files to");
    }
}
