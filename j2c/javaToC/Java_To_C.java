package javaToC;
import java.io.File;
import java.util.ArrayList;


public class Java_To_C {

    private ClassTypeJava[] javaClass;
    private ClassTypeC[] cClass;
    private String objectPersistName = "ObjectPersist";

    Java_To_C(String[] file) {

        System.out.println("Running ...");

        InputFileReader inputReader = new InputFileReader(file);
        String[] javaList = inputReader.getFileList();
        InputParameters ip = inputReader.getParameters();
        MessageOutput mo = new MessageOutput(ip.getOutputLevel());
        
        // Create object persistence class
        ObjectPersistGenerator cop = new ObjectPersistGenerator(objectPersistName, inputReader.getOutputDir());
        cop.createIncludeFile();
        cop.createCFile();

        // Parse all the java classes first.  Necessary because the fully
        // qualified path of some of the classes will be needed when
        // getting a method ID when calling into java.
        mo.printInfoMessage("  Creating java class instances...");
        ArrayList<ClassTypeJava> jList = new ArrayList<ClassTypeJava>();
        for(int i = 0; i < javaList.length; i++) {
            jList.add(new ClassTypeJava(javaList[i]));
        }
        mo.printInfoMessage("  Creating inner class instances...");
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
        mo.printInfoMessage("  Resolving java inheritance...");
        IR2 inherit = new IR2(javaClass);
        inherit.resolveInheritance();
       
        // Create C classes
        mo.printInfoMessage("  Creating C Class Instances...");
        for(int i = 0; i < javaClass.length; i++) {
            cClass[i] = new ClassTypeC(javaClass[i]);
            if(ip.useNamespace()) {
                if(ip.usePackageAsNamespace()) cClass[i].setNamespace(javaClass[i].getPackageName());
                else cClass[i].setNamespace(ip.getNamespace());
            }
        }

        ClassTypeContainer container = new ClassTypeContainer(cClass, javaClass);
        
        // Create object class
        ObjectClassCreator oCreate = new ObjectClassCreator(inputReader.getOutputDir(), container, mo);
        oCreate.createInterface();
        oCreate.createConcreteClass();
        
        // Create instance hash class
        InstanceHash iHash = new InstanceHash(inputReader.getOutputDir(), container);
        iHash.createClass();
        

        for(int i = 0; i < javaClass.length; i++) {

            mo.printInfoMessage("  Processing -> " + javaClass[i].getClassname());
            

            
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
	                                                    container, i, ip, objectPersistName,ir, mo);

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
