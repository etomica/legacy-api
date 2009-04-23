package javaToC;

import java.util.ArrayList;

public class IR2 {

    private ClassType[] classes;
    private ArrayList<String>[] myList;
    
    public IR2(ClassType[] ct) {
        classes = ct;
        myList = new ArrayList[classes.length];
        for(int i = 0; i < classes.length; i++) {
            myList[i] = new ArrayList<String>();
        }
    }
    
    public void resolveInheritance() {
//System.out.println("IN resolveInheritance()"); System.out.flush();
        ArrayList<ClassType> classList = new ArrayList<ClassType>();
        
        
        // Gather all classes that are a sub class
        for(int i = 0; i < classes.length; i++) {
            if(/*classes[i].isConcreteClass() &&*/
               (classes[i].getExtends().length != 0 ||
                classes[i].getImplements().length != 0)) {
                classList.add(classes[i]);
            }
        }
//System.out.println("size : " + classList.size());
        // Go thru the list of classes in classList and for each class
        // in classList, add itself as a subclass of any class that it
        // extends or implements
        for(int i = 0; i < classList.size(); i++) {
            for(int j = 0; j < classList.get(i).getExtends().length; j++) {
                try {
                    int idx = getJavaClassIndex(classList.get(i).getExtends()[j]);
//System.out.println("    ADDING TO LIST : " + classList.get(i).getClassname());System.out.flush();
                    myList[idx].add(classList.get(i).getClassname());
                }
                catch (ClassNotFoundException ex) {
                    System.out.println("Ignoring unknown inheritance class : " + classList.get(i).getExtends()[j]);
                }

            }

            for(int j = 0; j < classList.get(i).getImplements().length; j++) {

                try {
                    int idx = getJavaClassIndex(classList.get(i).getImplements()[j]);
//System.out.println(classList.get(i).getClassname() + " implements " + classes[idx].getClassname());
//System.out.println("java class index : " + classList.get(i).getImplements()[j] + "  idx = " + idx);
                    myList[idx].add(classList.get(i).getClassname());
                }
                catch (ClassNotFoundException ex) { ex.printStackTrace(); }
            }
        }

        // Go thru all classes and add as a subclass any subclass of its subclasses.
        // Need to dig down until all subclasses are added.
        for(int i = 0; i < myList.length; i++) {
//System.out.println(i + " out of " + myList.length + " complete -> working " + classes[i].getClassname());

            int lenBefore = 0;
            int lenAfter = myList[i].size();
            int startIdx = 0;
//System.out.println("  lenBefore : " + lenBefore + "  lenAfter : " + lenAfter);
//for(int j = 0; j < myList[i].size(); j++) {
//    System.out.println("    " + myList[i].get(j));
//}

            while(lenBefore != lenAfter) {
//                System.out.println("  lenBefore : " + lenBefore + "  lenAfter : " + lenAfter);
//                for(int j = 0; j < myList[i].size(); j++) {
//                    System.out.println("    " + myList[i].get(j));
//                }
                lenBefore = myList[i].size();
                // loop for all the subclasses added on the previous pass
                // If no subclasses were added on the prevous pass, the subclass
                // list is complete.
                for(int j = startIdx; j < lenAfter; j++) {
                    // loop for all classes
                    for(int k = 0; k < myList.length; k++) {
                        // for class in loop just above, loop for all of the classes it extends
                        for(int l = 0; l < classes[k].getExtends().length; l++) {
                            // if extend class is in the class being processed (outer most loop)
                            // then put the extend class's superclass in the class being
                            // processed subclass list (if it is not already in the list)
                            if(classes[k].getExtends()[l].compareTo(myList[i].get(j)) == 0) {
                                myList[i].add(classes[k].getClassname());
                            }
                        }
                        for(int l = 0; l < classes[k].getImplements().length; l++) {
                            if(classes[k].getImplements()[l].compareTo(myList[i].get(j)) == 0) {
                                myList[i].add(classes[k].getClassname());
                            }
                        }
                    }
                }
                startIdx = lenBefore;
                lenAfter = myList[i].size();
            }
        }
/*
for(int i = 0; i < classes.length; i++) {
System.out.println("CLASS : " + classes[i].getClassname());
for(int j = 0; j < myList[i].size(); j++) {
    System.out.println("  subclass : " + myList[i].get(j));
}
}
*/


        // Order the inheritance chain from the most derived to the
        // least derived
        for(int i = 0; i < myList.length; i++) {
//System.out.println(i + " out of " + myList.length + " complete -> working " + classes[i].getClassname());
            int prevSize = myList[i].size() + 1;
            while(myList[i].size() > 1 && prevSize > myList[i].size()) {
                prevSize = myList[i].size();
                
                ArrayList<String> toProcess = new ArrayList();
                for(int j = 0; j < myList[i].size(); j++) {
                    toProcess.add(myList[i].get(j));
                }
                
                for(int j = 0; j < toProcess.size(); j++) {
                    for(int k = 0; k < toProcess.size(); k++) {
                        if(j != k && !isSuperClassOf(toProcess.get(k), toProcess.get(j))) {

                            classes[i].addSubclass(toProcess.get(k));
                            for(int l = 0; l < myList[i].size(); l++) {
                                if(toProcess.get(k).compareTo(myList[i].get(l)) == 0) {
                                    myList[i].remove(l);
                                }
                            }
                        }
                    }
                }
            }
            if(myList[i].size() > 1) {
                System.out.println("WARNING : Class heirarchy for " + classes[i].getClassname() +
                    " is probably not correct.");
            }
            else if(myList[i].size() == 1) {

                classes[i].addSubclass(myList[i].get(0));
            }
        }
/*
for(int i = 0; i < classes.length; i++) {
System.out.println("CLASS : " + classes[i].getClassname());
for(int j = 0; j < classes[i].getSubclassList().length; j++) {
    System.out.println("  subclass : " + classes[i].getSubclassList()[j]);
}
}
*/      


    }

    /**
     * 
     * @param classname
     * @return Returns index into ClassType array held by this class for
     *         the given class name.
     * @throws ClassNotFoundException
     */
    private int getJavaClassIndex(String classname) throws ClassNotFoundException {
        for(int i = 0; i < classes.length; i++) {
            if(classname.compareTo(classes[i].getClassname()) == 0) return i;
        }
        throw new ClassNotFoundException("Required class does not appear to be in the input file : " + classname);
//            return -1;
    }

    /**
     * 
     * @param superClass
     * @param clz
     * @return Returns true if the second class given (clz) is a subclass
     *         of the first class given(superClass)
     */
    private boolean isSuperClassOf(String superClass, String clz) {
        int idx = -1;
        try {
            idx = getJavaClassIndex(superClass);
        }
        catch (ClassNotFoundException ex) {}
        
        for(int i = 0; i < myList[idx].size(); i++) {
            if(myList[idx].get(i).compareTo(clz) == 0) {
                return true;
            }
        }
        return false;
    }
}
