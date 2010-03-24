/*
 *  GlotzillaSimulationEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaSimulationEvent is an event superclass for events that are
      * related to some event within a simulation.
      */
    class GlotzillaSimulationEvent : public virtual IAPISimulationEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              */
            GlotzillaSimulationEvent(IAPISimulation *sim);

            IAPISimulation *getSimulation();

        protected:
            IAPISimulation *mSim;

    };
}
#endif
