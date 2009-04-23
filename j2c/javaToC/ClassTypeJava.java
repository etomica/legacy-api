package javaToC;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.Serializable;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.JApplet;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class ClassTypeJava extends ClassType {

    
//    private BufferedReader javaReader;
//    private String packageName = null;
    private Class myClass;
    
    public ClassTypeJava(String fullClassname) {
        super();
        
//System.out.println("CLASS : " + fullClassname);
        try {
            myClass = Class.forName(fullClassname);
        }
        catch (ClassNotFoundException ex) {
            ex.printStackTrace();
        }

//        printClassInfo();
        
        // className = myClass.getSimpleName();
        className = getClassname(myClass.getName());

        isInnerClass = myClass.getName().contains("$");
//System.out.println("ClassName : " + className + "  isInner : " + isInnerClass);

        jniClassname = new String(myClass.getName());
        jniClassname = jniClassname.replace(".", "/");
//System.out.println("JNIName  : " + jniClassname);

        int modifiers = myClass.getModifiers();
        
//        if(myClass.isInterface() == false) isConcreteClass = true;
//        else isConcreteClass = false;
        
        // Do not include Serializable, Comparable, Coneable
        // as an interface of the class
        ArrayList<String> iList = new ArrayList<String>();
        for(int i = 0; i < myClass.getInterfaces().length; i++) {
            if(isArgUsable(myClass.getInterfaces()[i].getSimpleName()) == true) {
                iList.add(getClassname(myClass.getInterfaces()[i].getName()));
            }
        }
        implementsList = new String[iList.size()];
        for(int i = 0; i < iList.size(); i++)
            implementsList[i] = iList.get(i);
        
        if(myClass.getSuperclass() == null)
            extendsList = new String[0];
        else {
            // Do not include Object as this classes superclass!
            if(isArgUsable(myClass.getSuperclass().getSimpleName()) == false) {
                extendsList = new String[0];
            }
            else {
                extendsList = new String[1];
                extendsList[0] = getClassname(myClass.getSuperclass().getName());
            }
        }
        
        numberOfCtors = myClass.getConstructors().length;
        ctorSignature = new String[numberOfCtors];
        for(int i = 0; i < myClass.getConstructors().length; i++) {

            Class[] ctorArgs = myClass.getConstructors()[i].getParameterTypes();
            String signature = new String("");
            for(int j = 0; j < ctorArgs.length; j++) {
                if(j != 0) signature = signature.concat(", ");
//System.out.println("CTOR ARG : " + ctorArgs[j].getSimpleName());
                signature = signature.concat(getClassname(ctorArgs[j].getName()));
            }
            ctorSignature[i] = signature;
//System.out.println("c SIGNATURE : " + ctorSignature[i]);
        }
        
        methodName = new String[myClass.getDeclaredMethods().length];
        methodSignature = new String[myClass.getDeclaredMethods().length];
        methodReturn = new String[myClass.getDeclaredMethods().length];

        for(int i = 0; i < myClass.getDeclaredMethods().length; i++) {
            methodName[i] = myClass.getDeclaredMethods()[i].getName();
//System.out.println("return : ");
//System.out.println("  " + myClass.getDeclaredMethods()[i].getReturnType().getName());
//System.out.println("  " +myClass.getDeclaredMethods()[i].getReturnType().getSimpleName());
//System.out.println("  " +myClass.getDeclaredMethods()[i].getReturnType().getCanonicalName());
            methodReturn[i] = getClassname(myClass.getDeclaredMethods()[i].getReturnType().getName());
            Class[] mySig = myClass.getDeclaredMethods()[i].getParameterTypes();
            String signature = new String("");
            for(int j = 0; j < mySig.length; j++) {
                if(j!= 0) signature = signature.concat(", ");
//System.out.println("    item : " + mySig[j].getName());
                signature = signature.concat(getClassname(mySig[j].getName()));
            }
//System.out.println("  sig : " + signature);
            methodSignature[i] = signature;
//System.out.println("m SIGNATURE : " + methodSignature[i]);
        }
        
        isStatic = new boolean[myClass.getDeclaredMethods().length];
        isFinal = new boolean[myClass.getDeclaredMethods().length];
        for(int i = 0; i < myClass.getDeclaredMethods().length; i++) {
            isStatic[i] = Modifier.isStatic(myClass.getDeclaredMethods()[i].getModifiers());
            isFinal[i] = Modifier.isFinal(myClass.getDeclaredMethods()[i].getModifiers());;
        }
        
        innerClasses = new ClassTypeJava[myClass.getDeclaredClasses().length];
        innerClassAccess = new String[myClass.getDeclaredClasses().length];
        
        for(int i = 0; i < innerClasses.length; i++) {
//System.out.println("  inner class -> " + myClass.getDeclaredClasses()[i].getName());
            innerClasses[i] = new ClassTypeJava(myClass.getDeclaredClasses()[i].getName());
            if(Modifier.isPublic(myClass.getDeclaredClasses()[i].getModifiers()) == true)
                innerClassAccess[i] = new String("public");
//            else if(Modifier.isProtected(myClass.getDeclaredClasses()[i].getModifiers()) == true)
//                innerClassAccess[i] = new String("protected");
//            else if(Modifier.isPrivate(myClass.getDeclaredClasses()[i].getModifiers()) == true)
//                innerClassAccess[i] = new String("private");
        }

    }

    public String getPackageName() {
//System.out.println("Package : " + myClass.getPackage().getName());
    	if(myClass.getPackage() != null)
            return myClass.getPackage().getName();
    	else
    		return "";
    }
    
    public String getClassname() {
        return className;
    }
    
    public String getFullClassname() {
        return myClass.getName();
    }
    
    public boolean isAbstractClass() {
        return Modifier.isAbstract(myClass.getModifiers());
    }
    
    public boolean isInterface() {
        return myClass.isInterface();
    }

    private void printClassInfo() {
    
        if(myClass.isInterface())
            System.out.println("INTERFACE : " + myClass.getSimpleName());
        else {
            if(isAbstractClass())
                System.out.println("ABSTRACT CLASS : " + myClass.getSimpleName());
            else
                System.out.println("CLASS : " + myClass.getSimpleName());
        }
        System.out.println("  canonical name : " + myClass.getCanonicalName());
        System.out.println("  name           : " + myClass.getName());
        System.out.println("  simple name    : " + myClass.getSimpleName());

        // Interfaces
        System.out.print("  interfaces     : ");
        Class[] myInterfaces = myClass.getInterfaces();
        for(int i = 0; i < myInterfaces.length; i++) {
            if(i != 0) System.out.print(", ");
            System.out.print(myInterfaces[i].getSimpleName());
        }
        System.out.println();
        // Superclass
        if(myClass.getSuperclass() != null)
            System.out.println("  superclass     : " + myClass.getSuperclass().getSimpleName());
        // Ctors
        Constructor[] myCtor = myClass.getConstructors();
        for(int i = 0; i < myCtor.length; i++) {
            if(i == 0) System.out.println("  ctors :");
            System.out.print("    " + myClass.getSimpleName() + "(");
            Class[] ctorArgs = myCtor[i].getParameterTypes();
            for(int j = 0; j < ctorArgs.length; j++) {
                if(j != 0) System.out.print(", ");
                System.out.print(ctorArgs[j].getSimpleName());
            }
            System.out.println(")");
        }
    
        Method[] myMethod = myClass.getDeclaredMethods();
        System.out.println("  methods :");
        for(int i = 0; i < myMethod.length; i++) {
            System.out.print("    " + myMethod[i].getReturnType().getSimpleName() + " ");
            System.out.print(myMethod[i].getName() + "(");
            Class[] mySig = myMethod[i].getParameterTypes();
            for(int j = 0; j < mySig.length; j++) {
                if(j!= 0) System.out.print(", ");
                System.out.print(mySig[j].getSimpleName());
            }
            System.out.println(")");
        }
    
        if(myClass.getDeclaredClasses().length > 0) {
            Class[] innerClasses = myClass.getDeclaredClasses();
            System.out.println("  inner classes :");
            for(int j = 0; j < innerClasses.length; j++) {
                System.out.println("    class = " + innerClasses[j].getSimpleName());
            }
        }

    }
    
    /**
     * 
     * @return Returns the name of the class.  An inner class
     *         replaces the '$' char with an underscore.
     */
    private String getClassname(String cName) {
        String name = new String(cName);

        int arrayCount = 0;
        
        if(name.startsWith("[")) {
            while(name.startsWith("[")) {
                name = name.replaceFirst("\\[", "");
                arrayCount++;
            }
//System.out.println("LEFTOVER : " + name);
            String type = TypeConversion.getJavaTypeForVMType(name.substring(0, 1));
            if(type.compareTo(TypeConversion.FULLY_QUALIFIED_CLASS) == 0) {
                name = name.substring(1);
            }
            else
                name = type;
        }
        
        if(name.contains("."))
            name = name.substring(name.lastIndexOf(".") + 1);
        
        if(name.contains("$"))
            name = name.replace("$", "_");

        if(name.contains(";"))
            name = name.replace(";", "");
        
        for(int i = 0; i < arrayCount; i++)
            name = name.concat("[]");
        
        return name;
    }
}
