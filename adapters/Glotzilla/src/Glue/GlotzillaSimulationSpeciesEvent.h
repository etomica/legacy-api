/*
 *  GlotzillaSimulationSpeciesEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONSPECIESEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONSPECIESEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesEvent.h"
#include "GlotzillaSimulationEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationSpeciesEvent : public GlotzillaSimulationEvent,
                                        public virtual IAPISimulationSpeciesEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              */
            GlotzillaSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species);

            /**
              * @return Returns the species that this event is related to.
              */
            IAPISpecies *getSpecies();

        protected:
            IAPISpecies *mSpecies;

    };
}
#endif
