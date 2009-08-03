/*
 *  GlotzillaSimulationListenerNative.h
 *  API Glue
 *
 */

#ifndef GLOTZ_NATIVESIMULATIONLISTENER_WRAPPER_H
#define GLOTZ_NATIVESIMULATIONLISTENER_WRAPPER_H

#include <glotzmd.h>

#include "jni.h"

#include "IAPISimulationListener.h"
#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationListenerNative : public virtual IAPISimulationListener {

        public:
            /**
              */
            GlotzillaSimulationListenerNative(JNIEnv *jenv, jobject jobj);

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
