package javaToC;

import java.io.BufferedWriter;

public class CSourceGenerationUtilities {

    private String methodID;
    private ClassTypeContainer container;
    
    public CSourceGenerationUtilities(String mID, ClassTypeContainer ctc) {
        methodID = new String(mID);
        container = ctc;
    }
    
    /**
     * The return value of the call to method ID is assigned to the value of
     * this classes methodID string.
     * @param methodName
     * @param methodReturn
     * @param signature
     * @param isStatic
     * @return Returns a string containing the line of code required to get the
     *         Java method ID for the method name/signature/return passed in.
     */
    public String constructMethodID(String methodName, String methodReturn,
                                     String signature, boolean isStatic) {

        return constructMethodID(methodName, methodReturn, signature, methodID, isStatic);
    }

    /**
     * 
     * @param methodName
     * @param methodReturn
     * @param signature
     * @param isStatic
     * @param varName The return value of the call to method ID is assigned to the value of
     *        this string.
     * @return Returns a string containing the line of code required to get the
     *         Java method ID for the method name/signature/return passed in.
     */
    public String constructMethodID(String methodName, String methodReturn,
                                     String signature, String varName, boolean isStatic) {
        
        String myVMReturn = new String(methodReturn);
        
        // Change local copy of ctor return type
        if(methodReturn.compareTo("") == 0) myVMReturn = "void";
        
        String myLine;
        if(isStatic)
            myLine = new String("jmethodID " + varName + " = (jenv)->GetStaticMethodID(myClass, ");
        else
            myLine = new String("jmethodID " + varName + " = (jenv)->GetMethodID(myClass, ");
        
//System.out.println("METHOD : " + methodName);
//System.out.println("  signature : " + signature);

//System.out.println("    sig : " + signature);
        String vmSig = getVMSignature(signature);
//System.out.println("    vmSig : " + vmSig);
        String vmType = TypeConversion.translateFromCToVMType(myVMReturn);
        if(vmType.compareTo(TypeConversion.FULLY_QUALIFIED_CLASS) == 0 ||
           vmType.compareTo("[" + TypeConversion.FULLY_QUALIFIED_CLASS) == 0) {
//System.out.println("myVMReturn : " + myVMReturn);
            try {
                vmType = vmType.concat(container.getCClass(myVMReturn).getJNIName() + ";");
            }
            catch (ClassNotFoundException ex) {
                System.out.println("Unknown type when creating JNI method signature: Will use java object");
                vmType = vmType.concat(Object.class.getName().replace(".", "/") + ";");
            }
        }

        String mn;
//System.out.println("METHOD RETURN ->" + methodReturn + "<-");
        if(methodReturn.compareTo("") == 0) mn = "\"<init>\"";
        else mn = "\"" + methodName + "\"";
            
        myLine = myLine.concat(mn + ", \"(" + vmSig + ")" + vmType + "\");");
        return myLine;

    }
    
    /**
     * 
     * @param signature The signature of the C method
     * @return Returns the VM signature required to get the Java method ID
     *         as a string.
     */
    private String getVMSignature(String signature) {
//System.out.println("signature : " + signature);
        String vm = new String("");
        String[] pairs = StringUtilities.parseCommaSeparatedList(signature);
        for(int i = 0; i < pairs.length; i++) {
            pairs[i] = StringUtilities.removeEdgeWhitespace(pairs[i]);
//System.out.println("    pair -> " + pairs[i]);
            String type = TypeConversion.translateFromCToVMType(pairs[i]);
            String nonArrayType = new String(type);
            nonArrayType = nonArrayType.replace("[", "");
            if(nonArrayType.compareTo(TypeConversion.FULLY_QUALIFIED_CLASS) == 0) {
                try {
                    type = type.concat(container.getCClass(pairs[i]).getJNIName() + ";");
                }
                catch (ClassNotFoundException ex) {
                    System.out.println("Unknown type when creating JNI method return: Will use java object");
                    type = type.concat(Object.class.getName().replace(".", "/") + ";");
                }
            }
//System.out.println("      type -> " + type);

            vm = vm.concat(type);
        }
        return vm;
    }

}
