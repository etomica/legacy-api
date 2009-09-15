/*
 *  TowheeBoxEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxEventManager.h"

namespace towheewrappers
{

    /*
     * addListener
     */
    void TowheeBoxEventManager::addListener(IAPIBoxListener *newListener) {
printf("TowheeBoxEventManager::addListener() NOT implemented yet.\n"); fflush(stdout);
//        mListeners.push_back(dynamic_cast<TowheeBoxListenerNative *>(newListener));
    }

    /*
     * removeListener
     */
    void TowheeBoxEventManager::removeListener(IAPIBoxListener *listener) {
printf("TowheeBoxEventManager::removeListener() NOT implemented yet.\n"); fflush(stdout);
    }

}
