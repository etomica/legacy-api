/*
 *  LammpsSimulationSpeciesIndexEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "LammpsSimulationSpeciesEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      */
    class LammpsSimulationSpeciesIndexEvent : public LammpsSimulationSpeciesEvent,
                                        public virtual IAPISimulationSpeciesIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            LammpsSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *species, int idx);

            /**
              * @return Returns the index that this event is related to.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
