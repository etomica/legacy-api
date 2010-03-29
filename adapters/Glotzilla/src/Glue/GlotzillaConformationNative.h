/*
 *  GlotzillaConformationNative.h
 *  API Glue
 *
 */

#ifndef GLOTZ_NATIVECONFORMATION_WRAPPER_H
#define GLOTZ_NATIVECONFORMATION_WRAPPER_H

#include <glotzmd.h>

#include "jni.h"

#include "IAPIAtomList.h"
#include "GlotzillaInterfaceConformation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * The class holds a java IConformation instance and when the
      * initializePositions method is called, calls the java IConformation
      * which holds the algorithm to determine the position of the atoms
      * within the molecule.
      *
      * This class is only used in simulations being written in Java.
      */
    class GlotzillaConformationNative : public virtual GlotzillaInterfaceConformation {

        public:
            /**
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java atom position
              *             definition class instance.
              */
            GlotzillaConformationNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            /**
              * Passes the call to the java conformation object held.
              * @param atomSet Atoms contained by the molecule
              */
            void initializePositions(IAPIAtomList *atomSet);

        private:
            jobject nativeObject;

    };
}

#endif
