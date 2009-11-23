/*
 *  TowheeNativeAtomPositionDefinition.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "IAPIMolecule.h"

#include "TowheeNativeAtomPositionDefinition.h"

namespace towheesnifferwrappers
{

    TowheeNativeAtomPositionDefinition::TowheeNativeAtomPositionDefinition
                                               (JNIEnv *jenv, jobject jobj, IAPISimulation *sim) {
        nativeObject = jenv->NewGlobalRef(jobj);
        mSim = dynamic_cast<TowheeSimulation *>(sim);
    }

    /*
     * position()
     */
    IAPIVector *TowheeNativeAtomPositionDefinition::position(IAPIMolecule *atom) {
        printf("TowheeNativeAtomPositionDefinition::position() This method should NOT be called\n");
    }

    /*
     * position()
     */
    IAPIVector *TowheeNativeAtomPositionDefinition::position(jobject atom) {

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

printf("TowheeNativeAtomPositionDefinition::position : NEED TO MAKE VECTOR\n"); fflush(stdout);

/*
        IAPIVectorMutable *vec = mSim->getSpace()->makeVector();

        if(mSim->getSpace()->getD() == 2) {
            jdouble x_pos = (jenv)->CallDoubleMethod(obj, xMethod, 0);
            jdouble y_pos = (jenv)->CallDoubleMethod(obj, xMethod, 1);
            double position[] =  {x_pos, y_pos};
            vec->E(position);
        }
        else if(mSim->getSpace()->getD() == 3) {
            jdouble x_pos = (jenv)->CallDoubleMethod(obj, xMethod, 0);
            jdouble y_pos = (jenv)->CallDoubleMethod(obj, xMethod, 1);
            jdouble z_pos = (jenv)->CallDoubleMethod(obj, xMethod, 2);
            double position[] =  {x_pos, y_pos, z_pos};
            vec->E(position);
        }
 
        return vec;
*/
    }
}

