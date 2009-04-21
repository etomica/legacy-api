package javaToC.junit.tests.Inheritance_Tests;

import javaToC.ClassTypeC;
import javaToC.ClassTypeJava;
import javaToC.InheritanceResolver;
import junit.framework.TestCase;

public class Inheritance_Tests extends TestCase {

    
    public void test_Inheritance_1_1() {
        
        String[] classes = {"ITest_1_1", "Test_1_1", "Test_1_2",
                            "Test_1_3", "Test_1_4" };
        
        ClassTypeJava[] ctj = new ClassTypeJava[classes.length];
        ClassTypeC[] ctc = new ClassTypeC[classes.length];
        
        for(int i = 0; i < classes.length; i++) {
            ctj[i] = new ClassTypeJava(classes[i]);
        }
  
        for(int i = 0; i < classes.length; i++) {
            ctc[i] = new ClassTypeC(ctj[i]);
        }

        InheritanceResolver ir = new InheritanceResolver(ctc);
        
        ir.resolveInheritance();
        
        // Inheritance of ITest_1_1
        String[] subclass;
        subclass = ctc[0].getSubclassList();
        assertEquals(4, subclass.length);
        // Order is not important for the next two
        boolean inherit1 = false;
        if(classes[4].compareTo(subclass[2]) == 0 ||
           classes[4].compareTo(subclass[3]) == 0) inherit1 = true;
        assertTrue(inherit1);
        boolean inherit2 = false;
        if(classes[3].compareTo(subclass[2]) == 0 ||
           classes[3].compareTo(subclass[3]) == 0) inherit2 = true;
        assertTrue(inherit2);
        assertEquals(classes[2], subclass[1]);
        assertEquals(classes[1], subclass[0]);
        
        // Inheritance of Test_1_1
        subclass = ctc[1].getSubclassList();
        assertEquals(3, subclass.length);
        // Order is not important for the next two
        inherit1 = false;
        if(classes[4].compareTo(subclass[1]) == 0 ||
           classes[4].compareTo(subclass[2]) == 0) inherit1 = true;
        assertTrue(inherit1);
        inherit2 = false;
        if(classes[3].compareTo(subclass[1]) == 0 ||
           classes[3].compareTo(subclass[2]) == 0) inherit2 = true;
        assertTrue(inherit2);
        assertEquals(classes[2], subclass[0]);
        
        // Inheritance of Test_1_2
        subclass = ctc[2].getSubclassList();
        assertEquals(1, subclass.length);
        assertEquals(classes[4], subclass[0]);
        
        // Inheritance of Test_1_3
        subclass = ctc[3].getSubclassList();
        assertEquals(0, subclass.length);

        // Inheritance of Test_1_4
        subclass = ctc[4].getSubclassList();
        assertEquals(0, subclass.length);
        
    }
    
    public void test_Inheritance_1_2() {
        
        String[] classes = {"ITest_1_1", "ITest_1_2", "Test_1_1", "Test_1_2",
                            "Test_1_3", "Test_1_4", "Test_1_5"};
        
        ClassTypeJava[] ctj = new ClassTypeJava[classes.length];
        ClassTypeC[] ctc = new ClassTypeC[classes.length];
        
        for(int i = 0; i < classes.length; i++) {
            ctj[i] = new ClassTypeJava(classes[i]);
        }
  
        for(int i = 0; i < classes.length; i++) {
            ctc[i] = new ClassTypeC(ctj[i]);
        }

        InheritanceResolver ir = new InheritanceResolver(ctc);
        
        ir.resolveInheritance();
        
        // Inheritance of ITest_1_1
        String[] subclass;
        subclass = ctc[0].getSubclassList();
        assertEquals(6, subclass.length);
        // Order is not important for the next two
        boolean inherit1 = false;
        if(classes[6].compareTo(subclass[2]) == 0 ||
           classes[6].compareTo(subclass[3]) == 0 ||
           classes[6].compareTo(subclass[4]) == 0 ||
           classes[6].compareTo(subclass[5]) == 0) inherit1 = true;
        assertTrue(inherit1);
        boolean inherit2 = false;
        if(classes[5].compareTo(subclass[2]) == 0 ||
           classes[5].compareTo(subclass[3]) == 0 ||
           classes[5].compareTo(subclass[4]) == 0 ||
           classes[5].compareTo(subclass[5]) == 0) inherit2 = true;
         assertTrue(inherit2);
         boolean inherit3 = false;
         if(classes[4].compareTo(subclass[2]) == 0 ||
            classes[4].compareTo(subclass[3]) == 0 ||
            classes[4].compareTo(subclass[4]) == 0 ||
            classes[4].compareTo(subclass[5]) == 0) inherit3 = true;
        assertTrue(inherit3);
        boolean inherit4 = false;
        if(classes[3].compareTo(subclass[2]) == 0 ||
           classes[3].compareTo(subclass[3]) == 0 ||
           classes[3].compareTo(subclass[4]) == 0 ||
           classes[3].compareTo(subclass[5]) == 0) inherit4 = true;
        assertTrue(inherit4);
        inherit2 = false;
        assertEquals(classes[2], subclass[1]);        
        assertEquals(classes[1], subclass[0]);
        
        // Inheritance of Test_1_1
        subclass = ctc[2].getSubclassList();
        assertEquals(3, subclass.length);
        // Order is not important for the next two
        inherit1 = false;
        if(classes[4].compareTo(subclass[1]) == 0 ||
           classes[4].compareTo(subclass[2]) == 0) inherit1 = true;
        assertTrue(inherit1);
        inherit2 = false;
        if(classes[5].compareTo(subclass[1]) == 0 ||
           classes[5].compareTo(subclass[2]) == 0) inherit2 = true;
        assertTrue(inherit2);
        assertEquals(classes[3], subclass[0]);
        
        // Inheritance of Test_1_2
        subclass = ctc[3].getSubclassList();
        assertEquals(1, subclass.length);
        assertEquals(classes[5], subclass[0]);
        
        // Inheritance of Test_1_3
        subclass = ctc[4].getSubclassList();
        assertEquals(0, subclass.length);

        // Inheritance of Test_1_4
        subclass = ctc[5].getSubclassList();
        assertEquals(0, subclass.length);
       
        // Inheritance ITest_1_2
        subclass = ctc[1].getSubclassList();
        assertEquals(1, subclass.length);
        assertEquals(classes[6], subclass[0]);

        // Inheritance Test_1_5
        subclass = ctc[6].getSubclassList();
        assertEquals(0, subclass.length);

    }

    public void test_Inheritance_2_1() {

        String[] classes = {"ITest_2_1", "ITest_2_2", "ITest_2_3", "Test_2_1" };
        
        ClassTypeJava[] ctj = new ClassTypeJava[classes.length];
        ClassTypeC[] ctc = new ClassTypeC[classes.length];
        
        for(int i = 0; i < classes.length; i++) {
            ctj[i] = new ClassTypeJava(classes[i]);
        }
  
        for(int i = 0; i < classes.length; i++) {
            ctc[i] = new ClassTypeC(ctj[i]);
        }

        InheritanceResolver ir = new InheritanceResolver(ctc);
        ir.resolveInheritance();
        // Inheritance of ITest_2_1
        String[] subclass;
        subclass = ctc[0].getSubclassList();
        assertEquals(3, subclass.length);
        // Order is not important for the next two
        boolean inherit1 = false;
        if(classes[2].compareTo(subclass[0]) == 0 ||
           classes[2].compareTo(subclass[1]) == 0) inherit1 = true;
        assertTrue(inherit1);
        boolean inherit2 = false;
        if(classes[1].compareTo(subclass[0]) == 0 ||
           classes[1].compareTo(subclass[1]) == 0) inherit2 = true;
        assertTrue(inherit2);       
        assertEquals(classes[3], subclass[2]);
        
    }
    
    
}
