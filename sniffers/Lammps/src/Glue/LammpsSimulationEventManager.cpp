/*
 *  LammpsSimulationEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationEventManager.h"

namespace lammpssnifferwrappers
{

    /*
     * addListener()
     */
    void LammpsSimulationEventManager::addListener(IAPISimulationListener *listener) {
        printf("LammpsSimulationEventManager::addListener() is NOT implemented.\n"); fflush(stdout);
    }

    /*
     * removeListener()
     */
    void LammpsSimulationEventManager::removeListener(IAPISimulationListener *listener) {
        printf("LammpsSimulationEventManager::removeListener() is NOT implemented.\n"); fflush(stdout);
    }

}
