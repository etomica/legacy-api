/*
 *  GlotzillaSimulationEventManager.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONEVTMGR_WRAPPER_H
#define GLOTZ_SIMULATIONEVTMGR_WRAPPER_H

#include <vector>

#include "IAPISimulationEventManager.h"
#include "IAPISimulationListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaSimulationEventManager fires simulation events to any
      * listeners registered to receive simulation events.  A listener is
      * notified of any simulation event whether the listener is interested
      * in the event or not.  If the listener is not interested in the event,
      * it can ignore the event.
      */
    class GlotzillaSimulationEventManager : public virtual IAPISimulationEventManager {

        public:
            void addListener(IAPISimulationListener *listener);
            void removeListener(IAPISimulationListener *listener);

        private:
            std::vector<IAPISimulationListener *>listeners;
    };
}

#endif
