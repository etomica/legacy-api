/*
 *  TowheeBoxListenerNative.cpp
 *  API Glue
 *
 *
 */

#include "jni.h"

#include "TowheeBoxListenerNative.h"
#include "TowheeBoxAtomEvent.h"
#include "TowheeBoxAtomIndexEvent.h"
#include "TowheeBoxMoleculeEvent.h"
#include "TowheeBoxMoleculeCountEvent.h"
#include "TowheeBoxMoleculeIndexEvent.h"
#include "TowheeBoxIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxListenerNative::TowheeBoxListenerNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * boxAtomAdded()
     */
    void TowheeBoxListenerNative::boxAtomAdded(IAPIBoxAtomEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxAtomEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxAtomEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomAddedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomAdded", "(Letomica/api/IBoxAtomEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomAddedMethod, event);
    }

    /*
     * boxAtomRemovedAdded()
     */
    void TowheeBoxListenerNative::boxAtomRemoved(IAPIBoxAtomEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxAtomEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxAtomEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomRemovedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomRemoved", "(Letomica/api/IBoxAtomEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomRemovedMethod, event);
    }

    /*
     * boxMoleculeAdded()
     */
    void TowheeBoxListenerNative::boxMoleculeAdded(IAPIBoxMoleculeEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxMoleculeEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxMoleculeEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeAddedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeAdded", "(Letomica/api/IBoxMoleculeEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeAddedMethod, event);
    }

    /*
     * boxMoleculeRemoved()
     */
    void TowheeBoxListenerNative::boxMoleculeRemoved(IAPIBoxMoleculeEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxMoleculeEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxMoleculeEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeRemovedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeRemoved", "(Letomica/api/IBoxMoleculeEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeRemovedMethod, event);
    }

    /*
     * boxGlobalAtomLeafIndexChanged()
     */
    void TowheeBoxListenerNative::boxGlobalAtomLeafIndexChanged(IAPIBoxIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxGlobalAtomLeafIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxGlobalAtomLeafIndexChanged", "(Letomica/api/IBoxIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxGlobalAtomLeafIndexChangedMethod, event);
    }

    /*
     * boxGlobalAtomIndexChanged()
     */
    void TowheeBoxListenerNative::boxGlobalAtomIndexChanged(IAPIBoxIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxGlobalAtomIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxGlobalAtomIndexChanged", "(Letomica/api/IBoxIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxGlobalAtomIndexChangedMethod, event);
    }

    /*
     * boxAtomLeafIndexChanged()
     */
    void TowheeBoxListenerNative::boxAtomLeafIndexChanged(IAPIBoxAtomIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxAtomIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxAtomIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxAtomLeafIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxAtomLeafIndexChanged", "(Letomica/api/IBoxAtomIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxAtomLeafIndexChangedMethod, event);
    }

    /*
     * boxMoleculeIndexChanged()
     */
    void TowheeBoxListenerNative::boxMoleculeIndexChanged(IAPIBoxMoleculeIndexEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxMoleculeIndexEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxMoleculeIndexEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxMoleculeIndexChangedMethod =
            (jenv)->GetMethodID(actionClass, "boxMoleculeIndexChanged", "(Letomica/api/IBoxMoleculeIndexEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxMoleculeIndexChangedMethod, event);
    }

    /*
     * boxNumberMolecules()
     */
    void TowheeBoxListenerNative::boxNumberMolecules(IAPIBoxMoleculeCountEvent *e) {

        JNIEnv *jenv = getJavaEnv();

        jclass eventClass = (jenv)->FindClass("towhee/wrapper/TowheeBoxMoleculeCountEvent");
        jmethodID eventCtor =
            (jenv)->GetMethodID(eventClass, "<init>", "(JZ)V");
        jobject event = (jenv)->NewObject(eventClass, eventCtor,
            (jlong)dynamic_cast<TowheeBoxMoleculeCountEvent *>(e), true);

        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID boxNumberMoleculesMethod =
            (jenv)->GetMethodID(actionClass, "boxNumberMolecules", "(Letomica/api/IBoxMoleculeCountEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, boxNumberMoleculesMethod, event);
    }

    /*
     * getJavaEnv()
     */
    JNIEnv *TowheeBoxListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }



}
