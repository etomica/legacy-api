package javaToC;

public class TypeConversion {

    private static int JAVA = 0;
    private static int CPP = 1;
    private static int NATIVE = 2;
    private static int VMTYPE = 3;
    private static int ARRAY_TYPE = 4;
    private static int JNI = 0;
    private static int STATIC_JNI = 1;
    private static int ARRAY_METHOD = 2;
    private static int ARRAY_FILL = 3;


    
	private static final String[][] types =
//	   Java Type    C++ Type   Native Type   VM TYPE                  array type               
	{ { "void",      "void",     "void",       "V",                   "N/A" },
      { "int",       "int",      "jint",       "I",                   "jintArray" },
      { "long",      "long",     "jlong",      "J",                   "jlongArray"},
      { "float",     "float",    "jfloat",     "F",                   "jfloatArray"},
      { "boolean",   "bool",     "jboolean",   "Z",                   "jbooleanArray"},
      { "double",    "double",   "jdouble",    "D",                   "jdoubleArray"},
      { "byte",      "unsigned char", "jbyte", "B",                   "jbyteArray"},
      { "short",     "short",    "jshort",     "S",                   "jshortArray"},
      { "String",    "char *",   "jstring",    "Ljava/lang/String;",  "jobjectArray"},
      { "char",      "char",     "jchar",      "C",                   "jcharArray" },
      { "final",     "const",    "N/A",        "N/A",                 "N/A" },
      { "static",    "static",   "N/A",        "N/A",                 "N/A" } };

	private static final String[][] methods =
//		JNI Method             Static JNI Method        // Array creation method
	{ { "CallVoidMethod",     "CallStaticVoidMethod",    "N/A",             "N/A" },
	  { "CallIntMethod",      "CallStaticIntMethod",     "NewIntArray",     "SetIntArrayRegion" },
	  { "CallLongMethod",     "CallStaticLongMethod",    "NewLongArray",    "SetLongArrayRegion"},
	  { "CallFloatMethod",    "CallStaticFloatMethod",   "NewFloatArray",   "SetFloatArrayRegion"},
	  { "CallBooleanMethod",  "CallStaticBooleanMethod", "NewBooleanArray", "SetBooleanArrayRegion"},
	  { "CallDoubleMethod",   "CallStaticDoubleMethod",  "NewDoubleArray",  "SetDoubleArrayRegion"},
	  { "CallByteMethod",     "CallStaticByteMethod",    "NewByteArray",    "SetByteArrayRegion"},
	  { "CallShortMethod",    "CallStaticShortMethod",   "NewShortArray",   "SetShortArrayRegion"},
	  { "CallObjectMethod",   "CallStaticObjectMethod",  "NewObjectArray",  "SetObjectArrayElement"},
	  { "CallCharMethod",     "CallStaticCharMethod",    "NewCharArray",    "SetCharArrayRegion" },
	  { "N/A",                "N/A",                     "N/A",             "N/A" },
	  { "N/A",                "N/A",                     "N/A",             "N/A" } };
	
	public static String FULLY_QUALIFIED_CLASS = "L";
	
    /**
     * 
     * @param javaType String containing a java type
     * @return Returns a string containing the C type for the Java type
     *         passed in.
     */
	static String getCType(String javaType) {
	    String cType = new String("");
	    // Remove array notation
	    while(javaType.contains("[]")) {
	        cType = cType.concat("[]");
	        javaType = javaType.replaceFirst("\\[\\]", "");
	    }
	    javaType = StringUtilities.removeEdgeWhitespace(javaType);
	    for(int i = 0; i < types.length; i++) {
	        if(javaType.compareTo(types[i][JAVA]) == 0) {
	            cType = types[i][CPP] + cType;
	            return cType;
	        }
	    }
	    return javaType + cType;
	}
    /**
     * 
     * @param cType String containing a C type
     * @return Returns true if the String containing a C type passed in
     *         is a C type.  Returns false if the C type is a user
     *         defined class.
     */
	static boolean isCType(String cType) {
	   // Remove array notation
	   cType = cType.replace("[]", "");
	   cType = StringUtilities.removeEdgeWhitespace(cType);
       for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return true;
            }
        }
       return false;
	}
    /**
     * 
     * @param javaType String containing a java type
     * @return Returns true if the String containing a java type passed in
     *         is a java type.  Returns false if the java type is a user
     *         defined class.
     */
    static boolean isJavaType(String javaType) {
        // Remove array notation
        javaType = javaType.replace("[]", "");
        javaType = StringUtilities.removeEdgeWhitespace(javaType);
        for(int i = 0; i < types.length; i++) {
            if(javaType.compareTo(types[i][JAVA]) == 0) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * 
     * @param nType String containing a java type
     * @return Returns true if the String containing a C type passed in
     *         is a native type.
     */
    static boolean isNativeType(String nType) {
        for(int i = 0; i < types.length; i++) {
            if(nType.compareTo(types[i][NATIVE]) == 0) {
                return true;
            }
        }
        return false;
    }
    /**
     * 
     * @param cType String containing a C type
     * @return Returns a string containing the JNI type signature for the c
     *         type passed in as a string.
     */
    static String translateFromCToVMType(String cType) {
        int arrayCount = 0;
        while(cType.contains("[]")) {
            arrayCount++;
            cType = cType.replaceFirst("\\[\\]", "");
        }
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                String ret = new String();
                for(int j = 0; j < arrayCount; j++)
                    ret = ret.concat("[");
                ret = ret.concat(types[i][VMTYPE]);
                return ret;
            }
        }
        String ret = new String();
        for(int j = 0; j < arrayCount; j++)
            ret = ret.concat("[");
        ret = ret.concat(FULLY_QUALIFIED_CLASS);
        return ret;
    }
    
    /**
     * 
     * @param jType String containing a java type
     * @return Returns true if the String containing a java type passed in
     *         is a "basic" building block.  i.e. One that can be passed
     *         from C++ to Java directly.
     */
    static boolean isBasicJavaType(String jType) {
        jType = jType.replace("[]", "");

        if(jType.compareTo("void")    == 0 ||
           jType.compareTo("int")     == 0 ||
           jType.compareTo("long")    == 0 ||
           jType.compareTo("float")   == 0 ||
           jType.compareTo("byte")    == 0 ||
           jType.compareTo("short")   == 0 ||
           jType.compareTo("boolean") == 0 ||
           jType.compareTo("char")    == 0 ||
           jType.compareTo("double")  == 0) return true;
        return false;
    }
    
    /**
     * 
     * @param cType String containing a java type
     * @return Returns true if the String containing a java type passed in
     *         is a "basic" building block.  i.e. One that can be passed
     *         from C++ to Java directly.
     */
    static boolean isBasicCType(String cType) {
        // Remove array notation
        cType = cType.replace("[]", "");
        cType = StringUtilities.removeEdgeWhitespace(cType);
        if(cType.compareTo("void")    == 0 ||
           cType.compareTo("int")     == 0 ||
           cType.compareTo("long")    == 0 ||
           cType.compareTo("float")   == 0 ||
           cType.compareTo("unsigned char")    == 0 ||
           cType.compareTo("short")   == 0 ||
           cType.compareTo("bool")    == 0 ||
           cType.compareTo("char")    == 0 ||
           cType.compareTo("char *")  == 0 ||
           cType.compareTo("double")  == 0) return true;
        return false;
    }

    /**
     * 
     * @param cType String containing a java type
     * @param isStatic Flag indicating if method is static
     * @return Returns a string containing the JNI method call that would be
     *         used when calling a java method from C for the C return
     *         type in the string passed in.
     */
    static String getJNIMethodForCType(String cType, boolean isStatic) {
        int idx;
        if(isStatic) idx = STATIC_JNI;
        else idx = JNI;
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return methods[i][idx];
            }
        }
        if(isStatic) return "CallStaticObjectMethod";
        else return "CallObjectMethod";
    }
    

    /**
     * 
     * @param cType
     * @return Returns the jni array type for the given c type
     */
    static String getArrayTypeForCType(String cType) {
    	cType = cType.replace("[]", "");
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return types[i][ARRAY_TYPE];
            }
        }

        return "jobjectArray";
    }
    
    /**
     * 
     * @param cType
     * @return Returns the jni array type for the given c type
     */
    static String getArrayMethodForCType(String cType) {
    	cType = cType.replace("[]", "");
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return methods[i][ARRAY_METHOD];
            }
        }

        return "NewObjectArray";
    }
    
    /**
     * 
     * @param cType
     * @return Returns the JNI method that is used to fill an array of the
     *         given C type.
     */
    static String getArrayFillForCType(String cType) {
    	cType = cType.replace("[]", "");
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return methods[i][ARRAY_FILL];
            }
        }

        return "SetObjectArrayElement";
    }
    /**
     * 
     * @param jType String containing a java type
     * @param isStatic Flag indicating if method is static
     * @return Returns a string containing the JNI method call that would be
     *         used when calling a java method from C for the java return
     *         type in the string passed in.
     */
    static String getJNIMethodForJavaType(String jType, boolean isStatic) {
        int idx;
        if(isStatic) idx = STATIC_JNI;
        else idx = JNI;
        for(int i = 0; i < types.length; i++) {
            if(jType.compareTo(types[i][JAVA]) == 0) {
                return methods[i][idx];
            }
        }
        if(isStatic) return "CallStaticObjectMethod";
        else return "CallObjectMethod";
    }
    
    /**
     * 
     * @param cType String containing a C type
     * @return Returns the native type for the given C type.
     */
    static String getNativeTypeForCType(String cType) {
        for(int i = 0; i < types.length; i++) {
            if(cType.compareTo(types[i][CPP]) == 0) {
                return types[i][NATIVE];
            }
        }
        return "jobject";
    }
    
    /**
     * 
     * @param jType String containing a Java type
     * @return Returns the native type for the given Java type.
     */
    static String getNativeTypeForJavaType(String jType) {
        for(int i = 0; i < types.length; i++) {
            if(jType.compareTo(types[i][JAVA]) == 0) {
                return types[i][NATIVE];
            }
        }
        return "jobject";
    }
    
    /**
     * 
     * @param vmType
     * @return Return the java type for the given java vm type
     */
    static String getJavaTypeForVMType(String vmType) {
        for(int i = 0; i < types.length; i++) {
            if(vmType.compareTo(types[i][VMTYPE]) == 0) {
                return types[i][JAVA];
            }
        }
        return FULLY_QUALIFIED_CLASS;
    }
    
}
