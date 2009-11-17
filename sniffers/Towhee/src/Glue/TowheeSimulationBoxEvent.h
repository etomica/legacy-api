/*
 *  TowheeSimulationBoxEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONBOXEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONBOXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPISimulationBoxEvent.h"
#include "TowheeSimulationEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationBoxEvent : public TowheeSimulationEvent,
                                        public virtual IAPISimulationBoxEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param box Box pertaining to this event.
              */
            TowheeSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box);

            /**
              * @return Returns the box that this event is related to.
              */
            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
