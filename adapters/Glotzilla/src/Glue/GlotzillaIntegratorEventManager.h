/*
 *  GlotzillaIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef GLOTZ_INTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define GLOTZ_INTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include <vector>

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"
#include "IAPISimulation.h"

#include "GlotzillaIntegratorListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaIntegratorEventManager is responsible for managing events
      * pertaining to the integrator.  Integrator event listeners can be
      * registered and unregistered with the integrator event manager.
      * The integrator event manager adds the listeners directly to the native
      * Glotzilla simulation, which handles dispatching the integrator events.
      */
    class GlotzillaIntegratorEventManager :
                                public virtual IAPIIntegratorEventManager {

        public:
            /**
              * GlotzillaIntegratorEventManager constructor
              * @param sim Simulation that the event manager belongs to.
              */			
            GlotzillaIntegratorEventManager(IAPISimulation *sim);

            // API Compliance
            void addListener(IAPIIntegratorListener *newListener);
            void removeListener(IAPIIntegratorListener *listener);

        private:
            IAPISimulation *mSim;
            std::map<IAPIIntegratorListener *, GlotzillaIntegratorListener *> mListeners;
    };
}
#endif
