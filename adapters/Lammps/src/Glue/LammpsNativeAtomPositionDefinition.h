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

    class LammpsNativeAtomPositionDefinition : public LammpsAtomPositionDefinition, public virtual LammpsInterfaceAtomPositionDefinition {

        public:
            LammpsNativeAtomPositionDefinition(JNIEnv *jenv, jobject jobj, IAPISimulation *sim);

            // API Compliance
            IAPIVector *position(IAPIMolecule *atom);

            // Non-API Methods
            IAPIVector *position(jobject atom);

        private:
            LammpsSimulation *mSim;
            jobject nativeObject;

    };
}
#endif
