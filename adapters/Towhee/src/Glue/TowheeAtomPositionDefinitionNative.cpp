/*
 *  TowheeAtomPositionDefinitionNative.cpp
 *  API Glue
 *
 */

#include "IAPIAtomPositioned.h"
#include "IAPIMolecule.h"

#include "TowheeAtomPositionDefinitionNative.h"

namespace towheewrappers
{

    TowheeAtomPositionDefinitionNative::TowheeAtomPositionDefinitionNative
                                               (JNIEnv *jenv, jobject jobj, TowheeSpace *space) {
        nativeObject = jenv->NewGlobalRef(jobj);
        mSpace = space;
    }

    /*
     * position()
     */
    IAPIVector *TowheeAtomPositionDefinitionNative::position(IAPIMolecule *atom) {
        printf("TowheeAtomPositionDefinitionNative::position() This method should NOT be called\n");
    }

    /*
     * position()
     */
    IAPIVector *TowheeAtomPositionDefinitionNative::position(jobject atom) {

        JavaVM *jvm;
        jint ret = JNI_GetCreatedJavaVMs(&jvm, 1, NULL);
        JNIEnv *jenv;
        (jvm)->AttachCurrentThread((void **)&jenv, NULL);

        jclass conformationClass = (jenv)->GetObjectClass(nativeObject);

        jmethodID positionMethod =
            (jenv)->GetMethodID(conformationClass,
                                "position",
                                "(Letomica/api/IMolecule;)Letomica/api/IVector;");

        jobject obj = (jenv)->CallObjectMethod(nativeObject, positionMethod, atom);

        jclass pos = (jenv)->GetObjectClass(obj);
        jmethodID xMethod =
            (jenv)->GetMethodID(pos, "x", "(I)D");

        IAPIVectorMutable *vec = mSpace->makeVector();

        if(mSpace->getD() == 2) {
            jdouble x_pos = (jenv)->CallDoubleMethod(obj, xMethod, 0);
            jdouble y_pos = (jenv)->CallDoubleMethod(obj, xMethod, 1);
            double position[] =  {x_pos, y_pos};
            vec->E(position);
        }
        else if(mSpace->getD() == 3) {
            jdouble x_pos = (jenv)->CallDoubleMethod(obj, xMethod, 0);
            jdouble y_pos = (jenv)->CallDoubleMethod(obj, xMethod, 1);
            jdouble z_pos = (jenv)->CallDoubleMethod(obj, xMethod, 2);
            double position[] =  {x_pos, y_pos, z_pos};
            vec->E(position);
        }
 
        return vec;
    }
}

