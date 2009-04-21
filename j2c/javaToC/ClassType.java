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
import java.io.Serializable;
import java.lang.reflect.Field;
import java.text.NumberFormat;
import java.text.ParsePosition;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Random;
import java.util.Vector;

import javax.swing.DefaultListModel;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class ClassType {

    
    protected String className = null;
    protected String jniClassname = null;
    protected String[] implementsList = null;
    protected String[] extendsList = null;
    protected String[] methodName = null;
    protected String[] methodSignature = null;
    protected String[] methodReturn = null;
    protected int numberOfCtors;
    protected String[] ctorSignature = null;
    protected boolean[] isStatic = null;
    protected boolean[] isFinal = null;
    protected boolean isInnerClass;
    protected ClassType[] innerClasses;
    protected String[] innerClassAccess;
//    protected boolean isConcreteClass;
    private ArrayList<String> subclassList;

  
    ClassType() {
        subclassList = new ArrayList();
    }
    
    /**
     * Add a class name to the list of this classes subclasses.  Do
     * not add if class is already in subclass list.
     * @param subclass
     */
    public void addSubclass(String subclass) {
        for(int i = 0; i < subclassList.size(); i++) {
            if(subclassList.get(i).compareTo(subclass) == 0) {
                return;
            }
        }
        subclassList.add(subclass);
    }
    
    public String[] getSubclassList() {
        String[] myList = new String[subclassList.size()];
        for(int i = 0; i < subclassList.size(); i++) {
            myList[i] = new String(subclassList.get(i));
        }
        return myList;
    }
    public String getClassname() {
        return className;
    }
    
    public String[] getImplements() {
        return implementsList;
    }
    
    public String[] getExtends() {
        return extendsList;
    }

    public String[] getMethodName() {
        return methodName;
    }
    
    public String[] getMethodSignature() {
        return methodSignature;
    }

    public String[] getMethodReturn() {
        return methodReturn;
    }
    
    public int getNumberOfCtors() {
        return numberOfCtors;
    }
    
    public String[] getCtorSignature() {
        return ctorSignature;
    }
    
    public boolean[] getFinal() {
        return isFinal;
    }
    
    public boolean[] getStatic() {
        return isStatic;
    }
    
    public ClassType[] getInnerClasses() {
        return innerClasses;
    }
    
    public String[] getInnerClassAccess() {
        return innerClassAccess;
    }
    
    public boolean isInnerClass() {
        return isInnerClass;
    }
    
    public String getJNIName() {
        return jniClassname;
    }
    
    protected boolean isArgUsable(String arg) {
        if(arg.compareTo(ActionEvent.class.getSimpleName())           != 0 &&
           arg.compareTo(ArrayList.class.getSimpleName())             != 0 &&
           arg.compareTo(ActionListener.class.getSimpleName())        != 0 &&
           arg.compareTo(Class.class.getSimpleName())                 != 0 &&
           arg.compareTo(Cloneable.class.getSimpleName())             != 0 &&
           arg.compareTo(Color.class.getSimpleName())                 != 0 &&
           arg.compareTo(Comparable.class.getSimpleName())            != 0 &&
           arg.compareTo(Component.class.getSimpleName())             != 0 &&
           arg.compareTo(DefaultListModel.class.getSimpleName())      != 0 &&
           arg.compareTo(Exception.class.getSimpleName())             != 0 &&
           arg.compareTo(Field.class.getSimpleName())                 != 0 &&
           arg.compareTo(File.class.getSimpleName())                  != 0 &&
           arg.compareTo(FileWriter.class.getSimpleName())            != 0 &&
           arg.compareTo(Graphics.class.getSimpleName())              != 0 &&
           arg.compareTo(HashMap.class.getSimpleName())               != 0 &&
           arg.compareTo(JApplet.class.getSimpleName())               != 0 &&
           arg.compareTo(JButton.class.getSimpleName())               != 0 &&
           arg.compareTo(JComboBox.class.getSimpleName())             != 0 &&
           arg.compareTo(JLabel.class.getSimpleName())                != 0 &&
           arg.compareTo(JList.class.getSimpleName())                 != 0 &&
           arg.compareTo(LinkedList.class.getSimpleName())            != 0 &&
           arg.compareTo(ListSelectionEvent.class.getSimpleName())    != 0 &&
           arg.compareTo(ListSelectionListener.class.getSimpleName()) != 0 &&
           arg.compareTo(Locale.class.getSimpleName())                != 0 &&
           arg.compareTo(Number.class.getSimpleName())                != 0 &&
           arg.compareTo(NumberFormat.class.getSimpleName())          != 0 &&
           arg.compareTo(ObjectOutputStream.class.getSimpleName())    != 0 &&
           arg.compareTo(ObjectInputStream.class.getSimpleName())     != 0 &&
           arg.compareTo(ParsePosition.class.getSimpleName())         != 0 &&
           arg.compareTo(PrintStream.class.getSimpleName())           != 0 &&
           arg.compareTo(Random.class.getSimpleName())                != 0 &&
           arg.compareTo(StringBuffer.class.getSimpleName())          != 0 &&
           arg.compareTo(Vector.class.getSimpleName())                != 0 &&
           arg.compareTo(Number.class.getSimpleName())                != 0 &&
           arg.compareTo(Object.class.getSimpleName())                != 0 &&
           arg.compareTo(ObjectOutputStream.class.getSimpleName())    != 0 &&
           arg.compareTo(ObjectInputStream.class.getSimpleName())     != 0 &&
           arg.compareTo(ParsePosition.class.getSimpleName())         != 0 &&
           arg.compareTo(PrintStream.class.getSimpleName())           != 0 &&
           arg.compareTo(Serializable.class.getSimpleName())          != 0 &&
           arg.compareTo(Throwable.class.getSimpleName())             != 0 &&
           arg.compareTo(Vector.class.getSimpleName())                != 0) {
            return true;
        }

        return false;
    }
}
