/*
 *  GlotzillaSimulationEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationEventManager.h"

namespace glotzwrappers
{

    /*
     * addListener
     */
    void GlotzillaSimulationEventManager::addListener(IAPISimulationListener *listener) {
        listeners.push_back(listener);
    }

    /*
     * removeListener
     */
    void GlotzillaSimulationEventManager::removeListener(IAPISimulationListener *listener) {
printf("GlotzillaSimulationEventManager::removeListener() NOT implemented yet.\n"); fflush(stdout);
//        listeners.erase(, +1);
    }

}
