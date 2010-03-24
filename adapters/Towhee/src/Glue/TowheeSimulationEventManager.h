/*
 *  TowheeSimulationEventManager.h
 *  API Glue
 *
 */


#ifndef TOWHEE_SIMULATION_EVENT_MANAGER_WRAPPER_H
#define TOWHEE_SIMULATION_EVENT_MANAGER_WRAPPER_H

#include "IAPISimulationEventManager.h"
#include "IAPISimulationListener.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeSimulationEventManager :
                                public virtual IAPISimulationEventManager {

        public:

            // API Compliance
            /**
              * This method is not implemented.
              */
            void addListener(IAPISimulationListener *newListener);
            /**
              * This method is not implemented.
              */
            void removeListener(IAPISimulationListener *listener);

    };
}
#endif
