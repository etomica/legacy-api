/*
 *  GlotzillaSimulationSpeciesIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "GlotzillaSimulationSpeciesEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationSpeciesIndexEvent : public GlotzillaSimulationSpeciesEvent,
                                        public virtual IAPISimulationSpeciesIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            GlotzillaSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *species, int idx);

            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
