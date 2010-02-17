/*
 *  TowheeConformationNative.cpp
 *  API Glue
 *
 *
 */

#include "jni.h"

#include "TowheeConformationNative.h"
#include "TowheeAtomList.h"

namespace towheesnifferwrappers
{

    TowheeConformationNative::TowheeConformationNative(JNIEnv *javaEnv, jobject jobj) {
        nativeObject = javaEnv->NewGlobalRef(jobj);
    }

    /*
     * initializePositions()
     */
    void TowheeConformationNative::initializePositions(IAPIAtomList *atomSet) {

        JavaVM *jvm = NULL;
        jsize no_vms;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, &no_vms);
        JNIEnv *jenv;
        (jvm)->AttachCurrentThread((void **)&jenv, NULL);


        jclass atomSetClass = (jenv)->FindClass("towhee/sniffer/wrapper/TowheeAtomList");
        jmethodID atomSetCtor = (jenv)->GetMethodID(atomSetClass, "<init>", "(JZ)V");
        jobject as = (jenv)->NewObject(atomSetClass, atomSetCtor, (jlong)atomSet, false);

        jclass conformationClass = (jenv)->GetObjectClass(nativeObject);
        jmethodID initializePositionsMethod =
            (jenv)->GetMethodID(conformationClass, "initializePositions", "(Letomica/api/IAtomList;)V");
        (jenv)->CallVoidMethod(nativeObject, initializePositionsMethod, as);

    }
}


