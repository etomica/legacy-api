/*
 *  TowheeIntegratorListenerNative.cpp
 *  API Glue
 *
 */

#include "TowheeIntegratorListenerNative.h"

namespace towheesnifferwrappers
{

    TowheeIntegratorListenerNative::TowheeIntegratorListenerNative(JNIEnv *jenv, jobject jobj) {
        nativeObject = jenv->NewGlobalRef(jobj);
    }

    /*
     * integratorInitialized()
     */
    void TowheeIntegratorListenerNative::integratorInitialized(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorInitialized =
            (jenv)->GetMethodID(actionClass, "integratorInitialized", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorInitialized, NULL);
    }

    /*
     * integratorStepStarted()
     */
    void TowheeIntegratorListenerNative::integratorStepStarted(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepStarted =
            (jenv)->GetMethodID(actionClass, "integratorStepStarted", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepStarted, NULL);
    }

    /*
     * integratorStepFinished()
     */
    void TowheeIntegratorListenerNative::integratorStepFinished(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepFinished =
            (jenv)->GetMethodID(actionClass, "integratorStepFinished", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepFinished, NULL);
    }

    /*
     * attachThread()
     */
    JNIEnv *TowheeIntegratorListenerNative::attachThread() {
        JavaVM *jvm;
        jsize vmCount;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }

    /*
     * detachThread()
     */
    void TowheeIntegratorListenerNative::detachThread() {
        JavaVM *jvm;
        jsize vmCount;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount);
        (jvm)->DetachCurrentThread();
    }
}
