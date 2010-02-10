/*
 *  LammpsIntegratorListenerNative.cpp
 *  API Glue
 *
 */

#include "LammpsIntegratorListenerNative.h"

namespace lammpssnifferwrappers
{

    LammpsIntegratorListenerNative::LammpsIntegratorListenerNative(JNIEnv *jenv, jobject jobj) {
        nativeObject = jenv->NewGlobalRef(jobj);
printf("CTOR : %x\n", this); fflush(stdout);
    }
	
    /*
     * integratorInitialized()
     */
    void LammpsIntegratorListenerNative::integratorInitialized(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = getJavaEnv();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorInitialized =
            (jenv)->GetMethodID(actionClass, "integratorInitialized", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorInitialized, NULL);
    }

    /*
     * integratorStepStarted()
     */
    void LammpsIntegratorListenerNative::integratorStepStarted(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = getJavaEnv();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepStarted =
            (jenv)->GetMethodID(actionClass, "integratorStepStarted", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepStarted, NULL);
    }

    /*
     * integratorStepFinished()
     */
    void LammpsIntegratorListenerNative::integratorStepFinished(IAPIIntegratorEvent *event) {
        JNIEnv *jenv = getJavaEnv();
        jclass actionClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID integratorStepFinished =
            (jenv)->GetMethodID(actionClass, "integratorStepFinished", "(Letomica/api/IIntegratorEvent;)V");
        (jenv)->CallVoidMethod(nativeObject, integratorStepFinished, NULL);
    }

    /*
     * getJavaEnv()
     */
    JNIEnv *LammpsIntegratorListenerNative::getJavaEnv() {
        JavaVM *jvm;
        jsize numVMs;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &numVMs);
        JNIEnv *env;
        (jvm)->AttachCurrentThread((void **)&env, NULL);
        return env;
    }

}
