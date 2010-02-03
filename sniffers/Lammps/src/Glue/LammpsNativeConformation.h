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

namespace lammpssnifferwrappers
{

    class LammpsNativeConformation : public LammpsConformation, public virtual LammpsInterfaceConformation {

        public:
            LammpsNativeConformation(JNIEnv *jenv, jobject jobj, IAPISimulation *sim);

            // API Compliance
            void initializePositions(IAPIAtomList *atomSet);

        private:
            jobject nativeObject;

    };
}

#endif
