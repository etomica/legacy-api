package javaToC;

public class InputParameters {

    private boolean useNamespace = false;
    private boolean usePackage = false;
    private String namespace = "DefaultNamespace";
    private boolean forwardDeclare = false;
    
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
    
}
