/*
 *  TowheeIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGRATOR_EVENT_MANAGER_WRAPPER_H
#define TOWHEE_INTEGRATOR_EVENT_MANAGER_WRAPPER_H

#include <vector>

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorEventManager :
                                public virtual IAPIIntegratorEventManager {

        public:

            TowheeIntegratorEventManager();

            // API Compliance
            void addListener(IAPIIntegratorListener *newListener);
            void removeListener(IAPIIntegratorListener *listener);

            // Non-API methods
            void stepStartedNotify();
            void stepCompletedNotify();

        private:
            std::vector<IAPIIntegratorListener *>mListeners;

    };
}
#endif
