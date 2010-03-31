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
      * A simulation listener that holds a java ISimulationListener and calls
      * the ISimulationListener's methods from its methods.
      */
    class GlotzillaSimulationListenerNative : public virtual IAPISimulationListener {

        public:
            /**
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java simulation
              *             listener class instance.
              */
            GlotzillaSimulationListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            /**
              * Method called by simulation event manager when a box is
              * added to the simulation.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationBoxAdded(IAPISimulationBoxEvent *e);
            /**
              * Method called by simulation event manager when a box is
              * removed to the simulation.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationBoxRemoved(IAPISimulationBoxEvent *e);
            /**
              * Method called by simulation event manager when a species is
              * added to the simulation.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationSpeciesAdded(IAPISimulationSpeciesEvent *e);
            /**
              * Method called by simulation event manager when a species is
              * removed to the simulation.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e);
            /**
              * Method called by simulation event manager when a specie's
              * index is changed.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e);
            void simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e);
            /**
              * Method called by simulation event manager when an atom
              * type's index is changed.  Passes the call to the java
              * simulation listener object held.
              * @param e Simulation event containing event information.
              */
            void simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e);
            void simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e);

        private:
            jobject nativeObject;
            JNIEnv *getJavaEnv();

    };
}

#endif
