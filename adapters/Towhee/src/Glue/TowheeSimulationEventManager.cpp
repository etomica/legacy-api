/*
 *  TowheeSimulationEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationEventManager.h"

namespace towheewrappers
{

    /*
     * addListener
     */
    void TowheeSimulationEventManager::addListener(IAPISimulationListener *newListener) {
printf("TowheeSimulationEventManager::addListener() NOT implemented yet.\n"); fflush(stdout);
//        mListeners.push_back(dynamic_cast<TowheeSimulationListenerNative *>(newListener));
    }

    /*
     * removeListener
     */
    void TowheeSimulationEventManager::removeListener(IAPISimulationListener *listener) {
printf("TowheeSimulationEventManager::removeListener() NOT implemented yet.\n"); fflush(stdout);
    }

}
