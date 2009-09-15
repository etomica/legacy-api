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
            void addListener(IAPISimulationListener *newListener);
            void removeListener(IAPISimulationListener *listener);

    };
}
#endif
