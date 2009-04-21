package javaToC;

import java.util.ArrayList;
/**
 * Class the determines a .h and .cpp file's include requirements.  Creates
 * a list of include requirements for both C++ files.  Looks at method
 * signatures and return types.
 * @author rrassler
 *
 */
public class ImportResolver {

    private ClassTypeC cct;
    private boolean usingForwardDeclarations;
    ArrayList<String> includeFileList;
    ArrayList<String> sourceFileList;
    
    public ImportResolver(boolean forward, ClassTypeC c) {
        cct = c;
        usingForwardDeclarations = forward;

        includeFileList = new ArrayList<String>();
        sourceFileList = new ArrayList<String>();
        
        generateIncludeList();
    }
    
    /**
     * 
     * @return Return list of classes that will require an include directive
     *         in the C++ include file.
     */
    public ArrayList<String> getIncludeFileList() {
        return includeFileList;
    }
    
    /**
     * 
     * @return Return list of classes that will require an include directive
     *         in the C++ source file.
     */
    public ArrayList<String> getSourceFileList() {
        return sourceFileList;
    }
    
    private void generateIncludeList() {
        ArrayList<String> dependencyList = new ArrayList<String>();

        // interfaces extended.  Need to be included in .h file.
        for(int i = 0; i < cct.getImplements().length; i++) {
            includeFileList.add(cct.getImplements()[i]);
        }
        // classes implemented.  Need to be included in .h file.
        for(int i = 0; i < cct.getExtends().length; i++) {
            includeFileList.add(cct.getExtends()[i]);
        }
        
        // Return Types and Method signatures
        for(int i = 0; i < cct.getMethodName().length; i++) {
            addToIncludeFromReturn(cct.getMethodReturn()[i], dependencyList);
            addToIncludeFromSignature(cct.getMethodSignature()[i], dependencyList);
        }
        // Ctor signatures
        for(int i = 0; i < cct.getNumberOfCtors(); i++) {
            addToIncludeFromSignature(cct.getCtorSignature()[i], dependencyList);
        }
        
        // Sort through dependencies to remove redundancy
        for(int i = 0; i < dependencyList.size(); i++) {
            boolean inList = false;
            // If dependency is already in list to be included in .h file,
            // remove it from consideration
            for(int j = 0; j < includeFileList.size(); j++) {
                if(includeFileList.get(j).compareTo(dependencyList.get(i)) == 0) {
                    inList = true;
                    break;
                }
            }
            // If dependency is already in list to be included in .cpp file,
            // remove it from consideration
            if(!inList) {
                for(int j = 0; j < sourceFileList.size(); j++) {
                    if(sourceFileList.get(j).compareTo(dependencyList.get(i)) == 0) {
                        inList = true;
                        break;
                    }
                }
            }
            // If the dependency is not already in list to be included in .h or
            // .cpp file, put it into the proper list depending on whether the
            // .h file is using forward declarations.
            if(!inList) {
                if(usingForwardDeclarations) {
                    sourceFileList.add(dependencyList.get(i));
                }
                else {
                    includeFileList.add(dependencyList.get(i));
                }
            }
        }
        
    }
    
    /**
     * Sort thru a method return type and pull out and dependencies that
     * may be required.
     * @param ret String containing the return type of a method
     * @param dependencyList list to put dependency into
     */
    private void addToIncludeFromReturn(String ret, ArrayList<String> dependencyList) {
        ArrayList<String> myList = new ArrayList();
        
        String returnType = StringUtilities.removeEdgeWhitespace(ret);
        
        // If the method is a ctor, just return
        if(returnType.compareTo("") == 0) return;
        
        // Break each item from the return type down
        // (static, final, int, char, etc...)
        String[] retItems = StringUtilities.parseBlankSeparatedList(returnType);
        
        // Loop over all items in return statement
        for(int i = 0; i < retItems.length; i++) {

            if(retItems[i].compareTo("static") == 0 ||
               retItems[i].compareTo("const")  == 0) {}
            else {
                // Remove array braces if present
                int idx;
                if((idx = retItems[i].indexOf("[]")) != -1) {
                    retItems[i] = retItems[i].substring(0, idx);
                }

                // special cases for a pointer (ex. char *) and
                // an unsigned (ex unsigned int) return.
                if(i < retItems.length-1) {
                    // pointer case
                    if(retItems[i+1].compareTo("*") == 0) {
                        myList.add(retItems[i]);
                        i++;
                    }
                    // unsigned case
                    else if(retItems[i].compareTo("unsigned") == 0) {
                        myList.add(retItems[i] + " " + retItems[i+1]);
                        i++;
                    }
                    // not a special case
                    else {
                        myList.add(retItems[i]);
                    }
                }
                // not a special case
                else {
                    myList.add(retItems[i]);
                }
            }
        }

        // List of return types is generated.  Not check to
        // see if they are native or user defined.
        for(int i = 0; i < myList.size(); i++) {

            // If the return type is user defined, then it needs
            // to be added to the dependency list.
            if(!TypeConversion.isCType(myList.get(i))) {
                dependencyList.add(myList.get(i));
            }
        }

    }
    
    /**
     * Sort thru a method signature and pull out and dependencies that
     * may be required.
     * @param sig String containing the return type of a method
     * @param dependencyList list to put dependency into
     */
    private void addToIncludeFromSignature(String sig, ArrayList<String> dependencyList) {

        String signature = StringUtilities.removeEdgeWhitespace(sig);
      
        String[] sigItems = StringUtilities.parseCommaSeparatedList(signature);
        // loop over each item in the method signature
        for(int j = 0; j < sigItems.length; j++) {
            // Replace pointer and array notation
            sigItems[j] = sigItems[j].replace("*", "");
            sigItems[j] = sigItems[j].replace("[]", "");
            sigItems[j] = StringUtilities.removeEdgeWhitespace(sigItems[j]);
            // If the type is user defined, then it needs
            // to be added to the dependency list.
            if(!TypeConversion.isCType(sigItems[j])) {
                dependencyList.add(sigItems[j]);
            }
        }
    }
    
}
