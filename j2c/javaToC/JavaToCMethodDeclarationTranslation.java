package javaToC;

import java.util.ArrayList;

/**
 * The class contains static methods that translate Java method
 * declarations into C method declarations.
 * 
 * @author rrassler
 *
 */
public abstract class JavaToCMethodDeclarationTranslation {
	
    /**
     * 
     * @param sig Signature of a java method
     * @return Return a C++ signature for the given java signature
     */
	public static String parseMethodSignature(String sig) {

        String signature = StringUtilities.removeEdgeWhitespace(sig);

		String returnType = new String("");
		
		// Break down signature items
    	String[] sigItems = StringUtilities.parseCommaSeparatedList(signature);
    	// Loop over each item in the signature list
    	for(int i = 0; i < sigItems.length; i++) {
            sigItems[i] = StringUtilities.removeEdgeWhitespace(sigItems[i]);

            String item = new String(sigItems[i]);
            item = item.replace("[]", "");
            if(ClassType.isArgUsable(item) == false) {
                if(sigItems[i].indexOf("[]") >= 0)
                    sigItems[i] = new String("WrapperObject" + sigItems[i].substring(sigItems[i].indexOf("[]")));
                else
                    sigItems[i] = new String("WrapperObject");
                
            }
            
            // signature item will be a pointer to a user defined object.
            // Add to signature list.
    	    if(!TypeConversion.isBasicJavaType(sigItems[i]) &&
    	        !sigItems[i].startsWith("String")) {

    	        returnType = returnType.concat(TypeConversion.getCType(sigItems[i]) + " *");
    	    }
    	    // Is a basic c type.  Add to signature list.
    	    else {
    	        returnType = returnType.concat(TypeConversion.getCType(sigItems[i]));
    	    }
    	    // Add the comma to separate signature items
    	    if(i < sigItems.length-1) returnType = returnType.concat(", ");

        }

        returnType = StringUtilities.removeEdgeWhitespace(returnType);

		return returnType;
	}
	
	/**
	 * 
	 * @param mn java method return type
	 * @return Returns string containing the C method return for the given
	 *         Java method return.
	 */
    public static String parseMethodReturn(String mn) {

        String myString = new String(mn);
         
        myString = StringUtilities.removeEdgeWhitespace(myString);

        // return a blank string for a constructor
        if(myString.compareTo("") == 0) return "";
        
        String[] items = StringUtilities.parseBlankSeparatedList(myString);

        String returnType = new String("");
         
        for(int i = 0; i < items.length; i++) {
            String item = new String(items[i]);
            item = item.replace("[]", "");
            if(ClassType.isArgUsable(item) == false) {
                if(items[i].indexOf("[]") >= 0)
                    items[i] = new String("WrapperObject" + items[i].substring(items[i].indexOf("[]")));
                else
                    items[i] = new String("WrapperObject");
            }

            returnType = returnType.concat(TypeConversion.getCType(items[i]) + " ");
        }

        returnType = StringUtilities.removeEdgeWhitespace(returnType);

        // Return all user defined classes as pointers unless return type
        // is an array
        if(!TypeConversion.isBasicCType(returnType) &&
           returnType.indexOf("[]") == -1) returnType = returnType.concat(" *");

        return returnType;
    }
    
}
