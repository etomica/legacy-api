/*
 *  TowheeSimulationEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeSimulationEvent is an event superclass for events that are
      * related to some event within a simulation.
      */
    class TowheeSimulationEvent : public virtual IAPISimulationEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              */
            TowheeSimulationEvent(IAPISimulation *sim);

            /**
              * @return Returns the simulation that this event is related to.
              */
            IAPISimulation *getSimulation();

        protected:
            IAPISimulation *mSim;

    };
}
#endif
