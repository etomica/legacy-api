/*
 *  LammpsSimulationBoxEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONBOXEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONBOXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPISimulationBoxEvent.h"
#include "LammpsSimulationEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSimulationBoxEvent : public LammpsSimulationEvent,
                                     public virtual IAPISimulationBoxEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param box Box pertaining to this event.
              */
            LammpsSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box);

            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
