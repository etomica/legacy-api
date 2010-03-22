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
            /**
              * Adds a listener that will be notified of integrator events.
              * @param newListener The listener to be notified of the
              *                    integrator events.
              */
            virtual void addListener(IAPIIntegratorListener *) = 0;
            /**
              * Removes a listener that was being notified of integrator
              * events.
              * @param listener The listener to be removed from the integrator
              *                 event notifications.
              */
            virtual void removeListener(IAPIIntegratorListener *) = 0;

    };
}
#endif
