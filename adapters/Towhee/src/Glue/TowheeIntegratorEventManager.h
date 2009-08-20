/*
 *  TowheeIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define TOWHEE_INTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorEventManager :
                                public virtual IAPIIntegratorEventManager {

        public:

            // API Compliance
            void addListener(IAPIIntegratorListener *newListener);
            void removeListener(IAPIIntegratorListener *listener);

            // Non-API methods
            void stepStartedNotify();
            void stepCompletedNotify();

    };
}
#endif
