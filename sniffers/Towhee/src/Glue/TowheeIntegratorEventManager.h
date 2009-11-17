/*
 *  TowheeIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define TOWHEE_INTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include <vector>

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"
#include "IAPISimulation.h"
#include "TowheeIntegratorListenerNative.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeIntegratorEventManager is responsible for managing events
      * pertaining to the integrator.  Integrator event listeners can be
      * registered and unregistered with the integrator event manager.
      * The integrator event manager adds the listeners directly to the native
      * Towhee simulation, which handles dispatching the integrator events.
      */
    class TowheeIntegratorEventManager :
                                public virtual IAPIIntegratorEventManager {

        public:

            // API Compliance
            /**
              * Adds a listener that will be notified of integrator events.
              * @param newListener The listener to be notified of the
              *                    integrator events.
              */
            void addListener(IAPIIntegratorListener *newListener);
            /**
              * Removes a listener that was being notified of integrator
              * events.
              * @param listener The listener to be removed from the integrator
              *                 event notifications.
              */
            void removeListener(IAPIIntegratorListener *listener);

            // Non-API methods
            void stepStartedNotify();
            void stepCompletedNotify();

        private:
            std::vector<TowheeIntegratorListenerNative *>mListeners;
    };
}
#endif
