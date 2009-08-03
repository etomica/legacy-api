/*
 *  GlotzillaIntegratorListenerNative.cpp
 *  API Glue
 *
 */


#include "GlotzillaIntegratorListenerNative.h"

namespace glotzwrappers
{

    GlotzillaIntegratorListenerNative::GlotzillaIntegratorListenerNative(JNIEnv *jenv, jobject jobj) {
        nativeObject = jenv->NewGlobalRef(jobj);
    }

    /*
     * ApplyPreMovePreForce()
     */
    void GlotzillaIntegratorListenerNative::ApplyPreMovePreForce() {
       integratorStepStarted(NULL);
    }

    /*
     * ApplyPostMovePostForce()
     */
    void GlotzillaIntegratorListenerNative::ApplyPostMovePostForce() {
       integratorStepFinished(NULL);
    }

    /*
     * integratorInitialized()
     */
    void GlotzillaIntegratorListenerNative::integratorInitialized(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorInitialized =
            (jenv)->GetMethodID(actionClass, "integratorInitialized", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorInitialized, NULL);
    }

    /*
     * integratorStepStarted()
     */
    void GlotzillaIntegratorListenerNative::integratorStepStarted(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepStarted =
            (jenv)->GetMethodID(actionClass, "integratorStepStarted", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepStarted, NULL);
    }

    /*
     * integratorStepFinished()
     */
    void GlotzillaIntegratorListenerNative::integratorStepFinished(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = attachThread();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepFinished =
            (jenv)->GetMethodID(actionClass, "integratorStepFinished", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepFinished, NULL);
    }

    /*
     * attachThread()
     */
    JNIEnv *GlotzillaIntegratorListenerNative::attachThread() {
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
    void GlotzillaIntegratorListenerNative::detachThread() {
        JavaVM *jvm;
        jsize vmCount;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount);
        (jvm)->DetachCurrentThread();
    }
}
