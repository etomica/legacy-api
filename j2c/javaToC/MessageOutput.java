package javaToC;

public class MessageOutput {

    private int outputLevel;
    
    public MessageOutput(int oLevel) {
        outputLevel = oLevel;
    }
    
    /**
     * Print an information message to the screen if information messages
     * are enabled.
     * @param message
     */
    public void printInfoMessage(String message) {
        if(outputLevel >= InputParameters.MESSAGES_INFO) {
            printMessage("INFO", message);
        }
    }
    
    /**
     * Print a warning message to the screen if warning messages
     * are enabled.
     * @param message
     */
    public void printWarningMessage(String message) {
        if(outputLevel >= InputParameters.MESSAGES_ALL) {
            printMessage("  WARNING", message);
        }
    }
    
    /**
     * Print an error message to the screen if error messages
     * are enabled.
     * @param message
     */
    public void printErrorMessage(String message) {
        if(outputLevel >= InputParameters.MESSAGES_ALL) {
            printMessage("  ERROR", message);
        }
    }
    
    private void printMessage(String pre, String message) {
        System.out.println(pre + " : " + message);
    }
    
}
