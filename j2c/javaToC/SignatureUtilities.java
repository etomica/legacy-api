package javaToC;

import java.util.ArrayList;

public class SignatureUtilities {

    public static String getSignature(MethodSignatureItem[] inSignature) {
        String signature = new String("");

        for(int i = 0; i < inSignature.length; i++) {
            if(i > 0) signature = signature.concat(", ");
            String varType = new String(inSignature[i].varType);

            varType = varType.replace("[]", "");
            signature = signature.concat(varType + " " +
                                         inSignature[i].varName);
            for(int j = 0; j < inSignature[i].arrayDimensions; j++)
            	signature = signature.concat("[]");
            for(int j = 0; j < inSignature[i].arrayDimensions; j++) {
                signature = signature.concat(", int " + inSignature[i].arrayArg[j]);
            }
        }

        return signature;
    }

    public static MethodSignatureItem[] parseMethodSignature(String inSignature) {
      
        ArrayList<MethodSignatureItem> mList = new ArrayList<MethodSignatureItem>();
        
        String[] items = StringUtilities.parseCommaSeparatedList(inSignature);
//System.out.println("================================");
        for(int j = 0; j < items.length; j++) {
            items[j] = StringUtilities.removeEdgeWhitespace(items[j]);
//System.out.println("item : " + items[j]);
            MethodSignatureItem mSig;
            mSig = new MethodSignatureItem(items[j], ("arg_" + j));
            mList.add(mSig);
        }

        MethodSignatureItem[] methodItems = new MethodSignatureItem[mList.size()];
        for(int i = 0; i < mList.size(); i++) {
            methodItems[i] = mList.get(i);
        }
        
        return methodItems;
        
    }
    
    public static class MethodSignatureItem {
        public int arrayDimensions = 0;
        public String varType = null;
        public String varName = null;
        public String arrayArg[];
        
        public MethodSignatureItem(String vType, String vName) {
//System.out.println("=========================================");

            varType = new String(vType);
            varName = new String(vName);
            if(varType.contains("[]")) {
                while(varType.contains("[]")) {
                    varType = vType.replaceFirst("\\[\\]", "");
                    arrayDimensions++;
                }
//System.out.println("varType : " + varType);
//System.out.println(" varName : " + varName);
//System.out.println("  ad : " + arrayDimensions);
//System.out.println("=========================================");
            }
            arrayArg = new String[arrayDimensions];
            for(int i = 0; i < arrayArg.length; i++) {
                arrayArg[i] = new String(varName + "__len_" + i);
            }
        }
    }

}
