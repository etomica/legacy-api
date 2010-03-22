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
            /**
              * This method is not implemented.
              */
            void removeListener(IAPIIntegratorListener *listener);

            // Non-API methods
            /**
              * Method called at the beginning of an integrator's step.
              */
            void stepStartedNotify();
            /**
              * Method called at the end of an integrator's step.
              */
            void stepCompletedNotify();

        private:
            std::vector<IAPIIntegratorListener *>mListeners;

    };
}
#endif
