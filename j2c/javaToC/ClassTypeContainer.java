package javaToC;

public class ClassTypeContainer {

    ClassTypeC[] cct;
    ClassTypeJava[] jct;
    
    public ClassTypeContainer(ClassTypeC[] c, ClassTypeJava[] j) {
        cct = c;
        jct = j;
    }
    
    /**
     * 
     * @return Return the number of C classes held by the container.
     */
    public int getCClassCount() {
        return cct.length;
    }
    
    /**
     * 
     * @param idx
     * @return
     */
    public ClassTypeC getCClass(int idx) {
        return cct[idx];
    }

    
    public ClassTypeC getCClass(String str) throws ClassNotFoundException {
        return cct[getCClassIndex(str)];
    }

    /**
     * 
     * @return Return the number of java classes held by the container.
     */
    public int getJavaClassCount() {
        return jct.length;
    }
    
    /**
     * 
     * @param idx
     * @return
     */
    public ClassTypeJava getJavaClass(int idx) {
        return jct[idx];
    }
    
//    public ClassTypeJava getJavaVlass(String str) throws ClassNotFoundException {
//        return jct[getJavaClassIndex(str)];
//    }
    
    /**
     * 
     * @param classname
     * @return
     * @throws ClassNotFoundException
     */
    public int getCClassIndex(String classname) throws ClassNotFoundException {

        classname = classname.replace("[]", "");
        classname = classname.replace("*", "");
        classname = StringUtilities.removeEdgeWhitespace(classname);
        for(int i = 0; i < cct.length; i++) {
            if(classname.compareTo(cct[i].getClassname()) == 0) return i;
        }
        throw new ClassNotFoundException("Required class does not appear to be in the input file : " + classname);

    }
}
