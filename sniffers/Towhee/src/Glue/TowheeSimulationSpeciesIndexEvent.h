/*
 *  TowheeSimulationSpeciesIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONSPECIESINDEXEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "TowheeSimulationSpeciesEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationSpeciesIndexEvent : public TowheeSimulationSpeciesEvent,
                                        public virtual IAPISimulationSpeciesIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param species Species pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            TowheeSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *species, int idx);

            /**
              * @return Returns the index that this event is related to.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
