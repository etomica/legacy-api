/*
 *  TowheeSimulationListenerNative.cpp
 *  API Glue
 *
 *
 */

#include "jni.h"

#include "TowheeSimulationListenerNative.h"
#include "TowheeSimulationBoxEvent.h"
#include "TowheeSimulationSpeciesEvent.h"
#include "TowheeSimulationSpeciesIndexEvent.h"
#include "TowheeSimulationAtomTypeIndexEvent.h"
#include "TowheeSimulationIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationListenerNative::TowheeSimulationListenerNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * simulationBoxAdded()
     */
    void TowheeSimulationListenerNative::simulationBoxAdded(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxAdded", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxAddedMethod, event);
    }

    /*
     * simulationBoxRemoved()
     */
    void TowheeSimulationListenerNative::simulationBoxRemoved(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxRemoved", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxRemovedMethod, event);
    }

    /*
     * simulationSpeciesAdded()
     */
    void TowheeSimulationListenerNative::simulationSpeciesAdded(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesAdded", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesAddedMethod, event);
    }

    /*
     * simulationSpeciesRemoved()
     */
    void TowheeSimulationListenerNative::simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesRemoved", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesRemovedMethod, event);
    }

    /*
     * simulationSpeciesIndexChanged()
     */
    void TowheeSimulationListenerNative::simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationSpeciesIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationSpeciesIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesIndexChanged", "(Letomica/api/ISimulationSpeciesIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesIndexChangedMethod, event);
    }

    /*
     * simulationSpeciesMaxIndexChanged()
     */
    void TowheeSimulationListenerNative::simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesMaxIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeIndexChanged()
     */
    void TowheeSimulationListenerNative::simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationAtomTypeIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationAtomTypeIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeIndexChanged", "(Letomica/api/ISimulationAtomTypeIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeMaxIndexChanged()
     */
    void TowheeSimulationListenerNative::simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeMaxIndexChangedMethod, event);
    }


    /*
     * getJavaEnv()
     */
    JNIEnv *TowheeSimulationListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }



}
