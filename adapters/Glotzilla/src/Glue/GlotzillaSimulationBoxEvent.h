/*
 *  GlotzillaSimulationBoxEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONBOXEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONBOXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPISimulationBoxEvent.h"
#include "GlotzillaSimulationEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationBoxEvent : public GlotzillaSimulationEvent,
                                        public virtual IAPISimulationBoxEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param box Box pertaining to this event.
              */
            GlotzillaSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box);

            /**
              * @return Returns the box that this event is related to.
              */
            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
