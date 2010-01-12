/*
 *  LammpsBoxEventManager.cpp
 *  API  Glue
 *
 */

#include "stdio.h"

#include "LammpsBoxEventManager.h"

namespace lammpssnifferwrappers
{

    /*
     * addListener()
     */
    void LammpsBoxEventManager::addListener(IAPIBoxListener *listener) {
        printf("LammpsBoxEventManager::addListener() is NOT implemented.\n"); fflush(stdout);
    }

    /*
     * removeListener()
     */
    void LammpsBoxEventManager::removeListener(IAPIBoxListener *listener) {
        printf("LammpsBoxEventManager::removeListener() is NOT implemented.\n"); fflush(stdout);
    }

}
