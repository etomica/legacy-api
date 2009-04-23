package javaToC;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.lang.reflect.Field;
import java.text.ParsePosition;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Random;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class ClassTypeC extends ClassType {

    private String namespace;
    private boolean abstractClass = false;
    private boolean pureVirtualClass = false; // all methods are pure virtual
    private boolean[] virtualMethods;

    public ClassTypeC(ClassTypeJava jct) {
        super();
        className = new String(jct.getClassname());
        jniClassname = new String(jct.getJNIName());
        isInnerClass = jct.isInnerClass();
        
        implementsList = jct.getImplements();
        extendsList = jct.getExtends();
//        isConcreteClass = jct.isConcreteClass;
        abstractClass = jct.isInterface() | jct.isAbstractClass();
        pureVirtualClass = jct.isInterface();

        // Ctor argument list
        ArrayList<String> ctorList = new ArrayList<String>();
        for(int i = 0; i < jct.getNumberOfCtors(); i++) {
            boolean ctorStatus = true;
//System.out.println("java ctor == " + jct.getCtorSignature()[i]);
            String[] args = StringUtilities.parseCommaSeparatedList(jct.getCtorSignature()[i]);
            for(int j = 0; j < args.length; j++) {
//System.out.println("arg : " + args[j]);
                if(/*isArgUsable(args[j]) == false ||*/
                   args[j].contains("[][]") == true) {
//System.out.println("  should not include this method");
                    ctorStatus = false;
                    break;
                }
            }
            
            if(ctorStatus)
                ctorList.add(JavaToCMethodDeclarationTranslation.parseMethodSignature(jct.getCtorSignature()[i]));

        }
        numberOfCtors = ctorList.size();
        ctorSignature = new String[numberOfCtors];
        for(int i = 0; i < numberOfCtors; i++) {
            ctorSignature[i] = ctorList.get(i);
//System.out.println("C SIG -> " + ctorSignature[i]);
        }
        
        ArrayList<String> methodList = new ArrayList<String>();
        ArrayList<String> signatureList = new ArrayList<String>();
        ArrayList<String> returnList = new ArrayList<String>();
        ArrayList<Boolean> staticList = new ArrayList<Boolean>();
        ArrayList<Boolean> finalList = new ArrayList<Boolean>();
        
        // Do not include any methods that return or accept as an argument
        // an Object of a Class
        for(int i = 0; i < jct.getMethodName().length; i++) {

//System.out.println("------------------------------------------------");
//System.out.println("ret -> " + jct.getMethodReturn()[i]);
//System.out.println("mn  -> " + jct.getMethodName()[i]);
//System.out.println("sig -> " + jct.getMethodSignature()[i]);
//System.out.println("Return ->" + jct.getMethodReturn()[i] + "<-");

            boolean sigStatus = true;
            String[] args = StringUtilities.parseCommaSeparatedList(jct.getMethodSignature()[i]);
            for(int j = 0; j < args.length; j++) {
//System.out.println("arg : " + args[j]);
                if(/*isArgUsable(args[j]) == false  ||*/
                   args[j].contains("[][]") == true) {
//System.out.println("  should not include this method");
                    sigStatus = false;
                    break;
                }
            }
            if(/*isArgUsable(jct.getMethodReturn()[i]) &&*/
               jct.getMethodReturn()[i].contains("[]") == false &&
               jct.getMethodName()[i].compareTo("main") != 0 &&
               sigStatus) {
                methodList.add(jct.getMethodName()[i]);
                signatureList.add(JavaToCMethodDeclarationTranslation.parseMethodSignature(jct.getMethodSignature()[i]));
                returnList.add(JavaToCMethodDeclarationTranslation.parseMethodReturn(jct.getMethodReturn()[i]));
                staticList.add(jct.getStatic()[i]);
                finalList.add(jct.getFinal()[i]);
            }
//else {System.out.println("    SKIPPING");}
        }

        methodName = new String[methodList.size()];
        methodSignature = new String[signatureList.size()];
        methodReturn = new String[returnList.size()];
        virtualMethods = new boolean[methodList.size()];
        isStatic = new boolean[staticList.size()];
        isFinal = new boolean[finalList.size()];

        for(int i = 0; i < methodList.size(); i++) {
            methodName[i] = methodList.get(i);
            methodSignature[i] = signatureList.get(i);
            methodReturn[i] = returnList.get(i);
            isStatic[i] = staticList.get(i);
            isFinal[i] = finalList.get(i);
            if(jct.isInterface()) virtualMethods[i] = true;
            else virtualMethods[i] = false;
        }
         
//        isStatic = jct.getStatic();
//        isFinal = jct.getFinal();

        String[] subclass = jct.getSubclassList();
//System.out.println("CLASS : " + className);
//System.out.println("  # subclasses : " + subclass.length);
        for(int i = 0; i < subclass.length; i++) {
            addSubclass(subclass[i]);
//System.out.println("    sc : " + subclass[i]);
        }
        
        innerClasses = new ClassTypeC[jct.getInnerClasses().length];
        innerClassAccess = new String[jct.getInnerClassAccess().length];
        for(int i = 0; i < innerClasses.length; i++) {
            innerClasses[i] = new ClassTypeC((ClassTypeJava)(jct.getInnerClasses()[i]));
            innerClassAccess[i] = jct.getInnerClassAccess()[i];
        }
    }
    
    public boolean[] getMethodVirtual() {
        return virtualMethods;
    }
    
    public void setNamespace(String n) {
        namespace = new String(n);
    }
    
    public String getNamespace() {
        return namespace;
    }
    
    public boolean isAbstractClass() {
        return abstractClass;
    }
    
    public boolean isPureVirtualClass() {
        return pureVirtualClass;
    }
    

}
