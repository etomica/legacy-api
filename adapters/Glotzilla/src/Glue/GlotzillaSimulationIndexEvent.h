/*
 *  GlotzillaSimulationIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONINDEXEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONINDEXEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationIndexEvent.h"
#include "GlotzillaSimulationEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationIndexEvent : public GlotzillaSimulationEvent,
                                        public virtual IAPISimulationIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            GlotzillaSimulationIndexEvent(IAPISimulation *sim, int idx);

            /**
              * @return Returns the index that this event is related to.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
