/*
 *  LammpsNativeConformation.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NATIVECONFORMATION_WRAPPER_H
#define LAMMPS_NATIVECONFORMATION_WRAPPER_H

#include "jni.h"

#include "IAPIAtomList.h"
#include "LammpsInterfaceConformation.h"
#include "IAPISimulation.h"

#include "LammpsConformation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * The class holds a java IConformation instance and when the
      * initializePositions method is called, calls the java IConformation
      * which holds the algorithm to determine the position of the atoms
      * within the molecule.
      *
      * This class is only used in simulations being written in Java.
      */
    class LammpsNativeConformation : public LammpsConformation, public virtual LammpsInterfaceConformation {

        public:
            /**
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java atom position
              *             definition class instance.
              */
            LammpsNativeConformation(JNIEnv *jenv, jobject jobj, IAPISimulation *sim);

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
