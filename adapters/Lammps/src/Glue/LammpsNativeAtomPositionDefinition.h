/*
 *  LammpsNativeAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NATIVEATOMPOSDEF_WRAPPER_H
#define LAMMPS_NATIVEATOMPOSDEF_WRAPPER_H

#include "jni.h"

#include "IAPIAtom.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "LammpsInterfaceAtomPositionDefinition.h"
#include "LammpsAtomPositionDefinition.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * The class holds a java IAtomPositionDefinition instance and when
      * the position method is called, calls the java IAtomPositionDefinition
      * which holds the algorithm to determine the position of the molecule.
      *
      * This class is only used in simulations being written in Java.
      */
    class LammpsNativeAtomPositionDefinition : public LammpsAtomPositionDefinition, public virtual LammpsInterfaceAtomPositionDefinition {

        public:
            /**
              *
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java atom position
              *             definition class instance.
              * @param sim Simulation that the atom position definition is a
              *            part of.
              */

            LammpsNativeAtomPositionDefinition(JNIEnv *jenv, jobject jobj, IAPISimulation *sim);

            // API Compliance
            /**
              * WARNING : This method should not be called.
              * @return Returns NULL.
              */
            IAPIVector *position(IAPIMolecule *atom);

            // Non-API Methods
            /**
              * Calls the position method on the java instance of the
              * IAtomPositionDefinition that this class holds and passes
              * the java instance of IMolecule that was passed in.  The
              * java object should determine the position of the molecule.
              * @param atom Is a java object which implements IMolecule.
              * @return Returns the position of the molecule as determined.
              */
            IAPIVector *position(jobject atom);

        private:
            LammpsSimulation *mSim;
            jobject nativeObject;

    };
}
#endif
