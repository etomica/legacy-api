/*
 *  GlotzillaNativeAtomPositionDefinition.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "IAPIMolecule.h"

#include "GlotzillaNativeAtomPositionDefinition.h"

namespace glotzwrappers
{

    GlotzillaNativeAtomPositionDefinition::GlotzillaNativeAtomPositionDefinition
                                               (JNIEnv *jenv, jobject jobj, IAPISimulation *sim) {
        nativeObject = jenv->NewGlobalRef(jobj);
        mSim = dynamic_cast<GlotzillaSimulation *>(sim);
    }

    /*
     * position()
     */
    IAPIVector *GlotzillaNativeAtomPositionDefinition::position(IAPIMolecule *atom) {
        printf("GlotzillaNativeAtomPositionDefinition::position() This method should NOT be called\n");
    }

    /*
     * position()
     */
    IAPIVector *GlotzillaNativeAtomPositionDefinition::position(jobject atom) {

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
    }
}

