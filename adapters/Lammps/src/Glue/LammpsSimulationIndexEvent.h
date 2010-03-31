/*
 *  LammpsSimulationIndexEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONINDEXEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONINDEXEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationIndexEvent.h"
#include "LammpsSimulationEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSimulationIndexEvent : public LammpsSimulationEvent,
                                        public virtual IAPISimulationIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            LammpsSimulationIndexEvent(IAPISimulation *sim, int idx);

            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
