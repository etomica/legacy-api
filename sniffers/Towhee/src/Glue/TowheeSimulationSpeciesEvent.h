/*
 *  TowheeSimulationSpeciesEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONSPECIESEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONSPECIESEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesEvent.h"
#include "TowheeSimulationEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationSpeciesEvent : public TowheeSimulationEvent,
                                        public virtual IAPISimulationSpeciesEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              */
            TowheeSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species);

            /**
              * @return Returns the species that this event is related to.
              */
            IAPISpecies *getSpecies();

        protected:
            IAPISpecies *mSpecies;

    };
}
#endif
