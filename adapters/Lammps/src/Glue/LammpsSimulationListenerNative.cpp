/*
 *  LammpsSimulationListenerNative.cpp
 *  API Glue
 *
 *
 */

#include "jni.h"

#include "LammpsSimulationListenerNative.h"
#include "LammpsSimulationBoxEvent.h"
#include "LammpsSimulationSpeciesEvent.h"
#include "LammpsSimulationSpeciesIndexEvent.h"
#include "LammpsSimulationAtomTypeIndexEvent.h"
#include "LammpsSimulationIndexEvent.h"

namespace lammpswrappers
{

    LammpsSimulationListenerNative::LammpsSimulationListenerNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * simulationBoxAdded()
     */
    void LammpsSimulationListenerNative::simulationBoxAdded(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxAdded", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxAddedMethod, event);
    }

    /*
     * simulationBoxRemoved()
     */
    void LammpsSimulationListenerNative::simulationBoxRemoved(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxRemoved", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxRemovedMethod, event);
    }

    /*
     * simulationSpeciesAdded()
     */
    void LammpsSimulationListenerNative::simulationSpeciesAdded(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesAdded", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesAddedMethod, event);
    }

    /*
     * simulationSpeciesRemoved()
     */
    void LammpsSimulationListenerNative::simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesRemoved", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesRemovedMethod, event);
    }

    /*
     * simulationSpeciesIndexChanged()
     */
    void LammpsSimulationListenerNative::simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationSpeciesIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationSpeciesIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesIndexChanged", "(Letomica/api/ISimulationSpeciesIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesIndexChangedMethod, event);
    }

    /*
     * simulationSpeciesMaxIndexChanged()
     */
    void LammpsSimulationListenerNative::simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesMaxIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeIndexChanged()
     */
    void LammpsSimulationListenerNative::simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationAtomTypeIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationAtomTypeIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeIndexChanged", "(Letomica/api/ISimulationAtomTypeIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeMaxIndexChanged()
     */
    void LammpsSimulationListenerNative::simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("lammps/wrapper/LammpsSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<LammpsSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeMaxIndexChangedMethod, event);
    }


    /*
     * getJavaEnv()
     */
    JNIEnv *LammpsSimulationListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }



}
