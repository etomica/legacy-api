/*
 *  LammpsSimulationSpeciesEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONSPECIESEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONSPECIESEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesEvent.h"
#include "LammpsSimulationEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      */
    class LammpsSimulationSpeciesEvent : public LammpsSimulationEvent,
                                        public virtual IAPISimulationSpeciesEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              */
            LammpsSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species);

            /**
              * @return Returns the species that this event is related to.
              */
            IAPISpecies *getSpecies();

        protected:
            IAPISpecies *mSpecies;

    };
}
#endif
