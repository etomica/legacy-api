package javaToC;

public class InputParameters {

    private boolean useNamespace = false;
    private boolean usePackage = false;
    private String namespace = "DefaultNamespace";
    private boolean forwardDeclare = false;
    private int outputLevel;

    public static final int MESSAGES_NONE = 0;
    public static final int MESSAGES_INFO = 1;
    public static final int MESSAGES_ALL = 2;
    
    public void setUseNamespace(boolean state) {
        useNamespace = state;
    }
    
    public boolean useNamespace() {
        return useNamespace;
    }
    
    public void setUsePackageAsNamespace(boolean state) {
        usePackage = state;
    }
    
    public boolean usePackageAsNamespace() {
        return usePackage;
    }
    
    public void setNamespace(String n) {
        namespace = n;
    }
    
    public String getNamespace() {
        return namespace;
    }
    
    public void setForwardDeclare(boolean f) {
        forwardDeclare = f;
    }
    
    public boolean getForwardDeclare() {
        return forwardDeclare;
    }
    
    public void setOutputLevel(int oLevel) {
        outputLevel = oLevel;
    }
    
    public int getOutputLevel() {
        return outputLevel;
    }
}
