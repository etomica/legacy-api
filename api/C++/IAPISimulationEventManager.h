/*
 *  IAPISimulationEventManager.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONEVENTMGR_WRAPPER_H
#define API_ISIMULATIONEVENTMGR_WRAPPER_H

#include "IAPISimulationListener.h"

namespace molesimAPI
{

    class IAPISimulationEventManager {

        public:			
            virtual void addListener(IAPISimulationListener *) = 0;
            virtual void removeListener(IAPISimulationListener *) = 0;

    };
}
#endif
