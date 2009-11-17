/*
 *  TowheeSimulationListenerNative.h
 *  API Glue
 *
 */

#ifndef TOWHEE_NATIVESIMULATIONLISTENER_WRAPPER_H
#define TOWHEE_NATIVESIMULATIONLISTENER_WRAPPER_H

#include "jni.h"

#include "IAPISimulationListener.h"
#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationListenerNative : public virtual IAPISimulationListener {

        public:
            /**
              */
            TowheeSimulationListenerNative(JNIEnv *jenv, jobject jobj);

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
