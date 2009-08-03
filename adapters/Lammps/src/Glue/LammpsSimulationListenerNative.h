/*
 *  LammpsSimulationListenerNative.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NATIVESIMULATIONLISTENER_WRAPPER_H
#define LAMMPS_NATIVESIMULATIONLISTENER_WRAPPER_H

#include "jni.h"

#include "IAPISimulationListener.h"
#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      */
    class LammpsSimulationListenerNative : public virtual IAPISimulationListener {

        public:
            /**
              */
            LammpsSimulationListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            /**
              */
            void simulationBoxAdded(IAPISimulationBoxEvent *e);
            void simulationBoxRemoved(IAPISimulationBoxEvent *e);
            void simulationSpeciesAdded(IAPISimulationSpeciesEvent *e);
            void simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e);
            void simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e);
            void simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e);
            void simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e);
            void simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e);

        private:
            jobject nativeObject;
            JNIEnv *getJavaEnv();

    };
}

#endif
