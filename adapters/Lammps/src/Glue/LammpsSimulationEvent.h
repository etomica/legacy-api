/*
 *  LammpsSimulationEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * LammpsSimulationEvent is an event superclass for events that are
      * related to some event within a simulation.
      */
    class LammpsSimulationEvent : public virtual IAPISimulationEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              */
            LammpsSimulationEvent(IAPISimulation *sim);

            IAPISimulation *getSimulation();

        protected:
            IAPISimulation *mSim;

    };
}
#endif
