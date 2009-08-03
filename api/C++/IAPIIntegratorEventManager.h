/*
 *  IAPIIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef API_IINTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define API_IINTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include "IAPIIntegratorListener.h"

namespace molesimAPI
{

    class IAPIIntegratorEventManager
    {
        public:			
            virtual void addListener(IAPIIntegratorListener *) = 0;		
            virtual void removeListener(IAPIIntegratorListener *) = 0;

    };
}
#endif
