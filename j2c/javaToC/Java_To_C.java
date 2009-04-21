package javaToC;
import java.io.File;
import java.util.ArrayList;


public class Java_To_C {

    private String inputFile;
    private ClassTypeJava[] javaClass;
    private ClassTypeC[] cClass;
    private String objectPersistName = "ObjectPersist";

    Java_To_C(String[] file) {

        System.out.println("Running ...");

        InputFileReader inputReader = new InputFileReader(file);
        String[] javaList = inputReader.getFileList();
        InputParameters ip = inputReader.getParameters();

        // Create object class
        ObjectClassCreator oCreate = new ObjectClassCreator(inputReader.getOutputDir());
        oCreate.createInterface();
        oCreate.createConcreteClass();
        
        // Create object persistence class
        ObjectPersistGenerator cop = new ObjectPersistGenerator(objectPersistName, inputReader.getOutputDir());
        cop.createIncludeFile();
        cop.createCFile();

        // Parse all the java classes first.  Necessary because the fully
        // qualified path of some of the classes will be needed when
        // getting a method ID when calling into java.
        System.out.println("  Creating java class instances...");
        ArrayList<ClassTypeJava> jList = new ArrayList<ClassTypeJava>();
        for(int i = 0; i < javaList.length; i++) {
            jList.add(new ClassTypeJava(javaList[i]));
        }
        System.out.println("  Creating inner class instances...");
        int startIdx = 0;
        int endIdx = jList.size();
        while(startIdx < endIdx) {
            for(int i = startIdx; i < endIdx; i++) {
                for(int j = 0; j < jList.get(i).getInnerClasses().length; j++) {
                    jList.add((ClassTypeJava)jList.get(i).getInnerClasses()[j]);
                }
            }
            startIdx = endIdx;
            endIdx = jList.size();
        }
   
        javaClass = new ClassTypeJava[jList.size()];
        cClass = new ClassTypeC[jList.size()];

        for(int i = 0; i < jList.size(); i++) {
            // Parse java file
            javaClass[i] = jList.get(i);
        }

//        InheritanceResolver inherit = new InheritanceResolver(javaClass);
        System.out.println("  Resolving java inheritance...");
        IR2 inherit = new IR2(javaClass);
        inherit.resolveInheritance();
       
        // Create C classes
        System.out.println("  Creating C Class Instances...");
        for(int i = 0; i < javaClass.length; i++) {
            cClass[i] = new ClassTypeC(javaClass[i]);
        }

        for(int i = 0; i < javaClass.length; i++) {

            System.out.println("    Processing   : " + javaClass[i].getClassname());
            
            if(ip.useNamespace()) {
                if(ip.usePackageAsNamespace()) cClass[i].setNamespace(javaClass[i].getPackageName());
                else cClass[i].setNamespace(ip.getNamespace());
            }
            
            ImportResolver ir = new ImportResolver(ip.getForwardDeclare(), cClass[i]);
            
            String includeFile = cClass[i].getClassname() + ".h";
            
            // Generate include file
            IncludeFileGenerator ifg =
                new IncludeFileGenerator(new File(inputReader.getOutputDir() + File.separator + includeFile),
                                         cClass[i], ip, ir);
            ifg.writeIncludeFile();
            
            // Generate C file
            if(!javaClass[i].isInterface()) {

	            String cFile = includeFile.replace(".h", ".cpp");
	            CFileGenerator cfg = new CFileGenerator(new File(inputReader.getOutputDir() + File.separator + cFile),
	                                                    cClass, javaClass, i, ip, objectPersistName,ir);

	            cfg.writeCFile();
            }
        }
        
        System.out.println("COMPLETE");
    }


    
    //
    // main()
    //
    public static void main(String[] args) {
        if(args.length < 1) {
            InputFileReader.printUsage();
            System.exit(-1);
        }
        Java_To_C jtoc = new Java_To_C(args);
    }

}
