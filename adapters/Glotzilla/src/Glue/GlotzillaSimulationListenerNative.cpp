/*
 *  GlotzillaSimulationListenerNative.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "jni.h"

#include "GlotzillaSimulationListenerNative.h"
#include "GlotzillaSimulationBoxEvent.h"
#include "GlotzillaSimulationSpeciesEvent.h"
#include "GlotzillaSimulationSpeciesIndexEvent.h"
#include "GlotzillaSimulationAtomTypeIndexEvent.h"
#include "GlotzillaSimulationIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationListenerNative::GlotzillaSimulationListenerNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * simulationBoxAdded()
     */
    void GlotzillaSimulationListenerNative::simulationBoxAdded(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxAdded", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxAddedMethod, event);
    }

    /*
     * simulationBoxRemoved()
     */
    void GlotzillaSimulationListenerNative::simulationBoxRemoved(IAPISimulationBoxEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationBoxEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationBoxEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationBoxRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationBoxRemoved", "(Letomica/api/ISimulationBoxEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationBoxRemovedMethod, event);
    }

    /*
     * simulationSpeciesAdded()
     */
    void GlotzillaSimulationListenerNative::simulationSpeciesAdded(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesAddedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesAdded", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesAddedMethod, event);
    }

    /*
     * simulationSpeciesRemoved()
     */
    void GlotzillaSimulationListenerNative::simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationSpeciesEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationSpeciesEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesRemovedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesRemoved", "(Letomica/api/ISimulationSpeciesEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesRemovedMethod, event);
    }

    /*
     * simulationSpeciesIndexChanged()
     */
    void GlotzillaSimulationListenerNative::simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationSpeciesIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationSpeciesIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesIndexChanged", "(Letomica/api/ISimulationSpeciesIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesIndexChangedMethod, event);
    }

    /*
     * simulationSpeciesMaxIndexChanged()
     */
    void GlotzillaSimulationListenerNative::simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationSpeciesMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationSpeciesMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationSpeciesMaxIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeIndexChanged()
     */
    void GlotzillaSimulationListenerNative::simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationAtomTypeIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationAtomTypeIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeIndexChanged", "(Letomica/api/ISimulationAtomTypeIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeIndexChangedMethod, event);
    }

    /*
     * simulationAtomTypeMaxIndexChanged()
     */
    void GlotzillaSimulationListenerNative::simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaSimulationIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaSimulationIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID simulationAtomTypeMaxIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "simulationAtomTypeMaxIndexChanged", "(Letomica/api/ISimulationIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, simulationAtomTypeMaxIndexChangedMethod, event);
    }


    /*
     * getJavaEnv()
     */
    JNIEnv *GlotzillaSimulationListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }



}
