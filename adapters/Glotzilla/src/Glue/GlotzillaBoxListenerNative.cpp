/*
 *  GlotzillaBoxListenerNative.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "jni.h"

#include "GlotzillaBoxListenerNative.h"
#include "GlotzillaBoxAtomEvent.h"
#include "GlotzillaBoxAtomIndexEvent.h"
#include "GlotzillaBoxMoleculeEvent.h"
#include "GlotzillaBoxMoleculeCountEvent.h"
#include "GlotzillaBoxMoleculeIndexEvent.h"
#include "GlotzillaBoxIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxListenerNative::GlotzillaBoxListenerNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * boxAtomAdded()
     */
    void GlotzillaBoxListenerNative::boxAtomAdded(IAPIBoxAtomEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxAtomEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxAtomEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomAddedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomAdded", "(Letomica/api/IBoxAtomEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomAddedMethod, event);
    }

    /*
     * boxAtomRemovedAdded()
     */
    void GlotzillaBoxListenerNative::boxAtomRemoved(IAPIBoxAtomEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxAtomEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxAtomEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomRemovedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomRemoved", "(Letomica/api/IBoxAtomEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomRemovedMethod, event);
    }

    /*
     * boxMoleculeAdded()
     */
    void GlotzillaBoxListenerNative::boxMoleculeAdded(IAPIBoxMoleculeEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxMoleculeEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxMoleculeEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeAddedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeAdded", "(Letomica/api/IBoxMoleculeEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeAddedMethod, event);
    }

    /*
     * boxMoleculeRemoved()
     */
    void GlotzillaBoxListenerNative::boxMoleculeRemoved(IAPIBoxMoleculeEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxMoleculeEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxMoleculeEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeRemovedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeRemoved", "(Letomica/api/IBoxMoleculeEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeRemovedMethod, event);
    }

    /*
     * boxGlobalAtomLeafIndexChanged()
     */
    void GlotzillaBoxListenerNative::boxGlobalAtomLeafIndexChanged(IAPIBoxIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxGlobalAtomLeafIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxGlobalAtomLeafIndexChanged", "(Letomica/api/IBoxIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxGlobalAtomLeafIndexChangedMethod, event);
    }

    /*
     * boxGlobalAtomIndexChanged()
     */
    void GlotzillaBoxListenerNative::boxGlobalAtomIndexChanged(IAPIBoxIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxGlobalAtomIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxGlobalAtomIndexChanged", "(Letomica/api/IBoxIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxGlobalAtomIndexChangedMethod, event);
    }

    /*
     * boxAtomLeafIndexChanged()
     */
    void GlotzillaBoxListenerNative::boxAtomLeafIndexChanged(IAPIBoxAtomIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxAtomIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxAtomIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomLeafIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomLeafIndexChanged", "(Letomica/api/IBoxAtomIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomLeafIndexChangedMethod, event);
    }

    /*
     * boxMoleculeIndexChanged()
     */
    void GlotzillaBoxListenerNative::boxMoleculeIndexChanged(IAPIBoxMoleculeIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxMoleculeIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxMoleculeIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeIndexChanged", "(Letomica/api/IBoxMoleculeIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeIndexChangedMethod, event);
    }

    /*
     * boxNumberMolecules()
     */
    void GlotzillaBoxListenerNative::boxNumberMolecules(IAPIBoxMoleculeCountEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("glotz/wrapper/GlotzillaBoxMoleculeCountEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<GlotzillaBoxMoleculeCountEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxNumberMoleculesMethod =
            (jenv)->GetMethodID(actionClass, "boxNumberMolecules", "(Letomica/api/IBoxMoleculeCountEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxNumberMoleculesMethod, event);
    }

    /*
     * getJavaEnv()
     */
    JNIEnv *GlotzillaBoxListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }



}
