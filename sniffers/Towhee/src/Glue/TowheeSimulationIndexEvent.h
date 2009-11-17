/*
 *  TowheeSimulationIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONINDEXEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONINDEXEVENT_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISimulationIndexEvent.h"
#include "TowheeSimulationEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationIndexEvent : public TowheeSimulationEvent,
                                        public virtual IAPISimulationIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            TowheeSimulationIndexEvent(IAPISimulation *sim, int idx);

            /**
              * @return Returns the index that this event is related to.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
