package javaToC;

import java.util.ArrayList;

public class InheritanceResolver {

    private ClassType[] classes;
    
    public InheritanceResolver(ClassType[] ct) {
        classes = ct;
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
                    classes[idx].addSubclass(classList.get(i).getClassname());
                }
                catch (ClassNotFoundException ex) { ex.printStackTrace(); }

            }

            for(int j = 0; j < classList.get(i).getImplements().length; j++) {

                try {
                    int idx = getJavaClassIndex(classList.get(i).getImplements()[j]);

//System.out.println("java class index : " + classList.get(i).getImplements()[j] + "  idx = " + idx);
                    classes[idx].addSubclass(classList.get(i).getClassname());
                }
                catch (ClassNotFoundException ex) { ex.printStackTrace(); }
            }
        }

        // Go thru all classes and add as a subclass any subclass of its subclasses.
        // Need to dig down until all subclasses are added.
        for(int i = 0; i < classes.length; i++) {
            int lenBefore = 0;
            int lenAfter = classes[i].getSubclassList().length;;
            int startIdx = 0;
            while(lenBefore != lenAfter) {
                lenBefore = classes[i].getSubclassList().length;
                // loop for all the subclasses added on the previous pass
                // If no subclasses were added on the prevous pass, the subclass
                // list is complete.
                for(int j = startIdx; j < lenAfter; j++) {
                    // loop for all classes
                    for(int k = 0; k < classes.length; k++) {
                        // for class in loop just above, loop for all of the classes it extends
                        for(int l = 0; l < classes[k].getExtends().length; l++) {
                            // if extend class is in the class being processed (outer most loop)
                            // then put the extend class's superclass in the class being
                            // processed subclass list (if it is not already in the list)
                            if(classes[k].getExtends()[l].compareTo(classes[i].getSubclassList()[j]) == 0) {
                                classes[i].addSubclass(classes[k].getClassname());
                            }
                        }
                        for(int l = 0; l < classes[k].getImplements().length; l++) {
                            if(classes[k].getImplements()[l].compareTo(classes[i].getSubclassList()[j]) == 0) {
                                classes[i].addSubclass(classes[k].getClassname());
                            }
                        }
                    }
                }
                startIdx = lenBefore;
                lenAfter = classes[i].getSubclassList().length;
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



    private int getJavaClassIndex(String classname) throws ClassNotFoundException {
        for(int i = 0; i < classes.length; i++) {
            if(classname.compareTo(classes[i].getClassname()) == 0) return i;
        }
        throw new ClassNotFoundException("Required class does not appear to be in the input file : " + classname);
//        return -1;
    }
}
