/*
 *  GlotzillaConformationNative.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "jni.h"

#include "GlotzillaConformationNative.h"
#include "GlotzillaAtomList.h"

namespace glotzwrappers
{

    GlotzillaConformationNative::GlotzillaConformationNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * initializePositions()
     */
    void GlotzillaConformationNative::initializePositions(IAPIAtomList *atomSet) {

        JavaVM *jvm = NULL;
        jsize no_vms;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &no_vms);
        JNIEnv *jenv;
        (jvm)->AttachCurrentThread((void **)&jenv, NULL);


        jclass atomSetClass = (jenv)->FindClass("glotz/wrapper/GlotzillaAtomList");
        jmethodID atomSetCtor = (jenv)->GetMethodID(atomSetClass, "<init>", "(JZ)V");
        jobject as = (jenv)->NewObject(atomSetClass, atomSetCtor, (jlong)atomSet, false);

        jclass conformationClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID initializePositionsMethod =
            (jenv)->GetMethodID(conformationClass, "initializePositions", "(Letomica/api/IAtomList;)V");
        (jenv)->CallVoidMethod(nativeObject, initializePositionsMethod, as);

    }
}


