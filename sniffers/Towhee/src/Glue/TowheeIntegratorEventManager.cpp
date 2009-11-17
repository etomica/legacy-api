/*
 *  TowheeIntegratorEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeIntegratorEventManager.h"

namespace towheesnifferwrappers
{

    /*
     * addListener
     */
    void TowheeIntegratorEventManager::addListener(IAPIIntegratorListener *newListener) {
        mListeners.push_back(dynamic_cast<TowheeIntegratorListenerNative *>(newListener));

    }

    /*
     * removeListener
     */
    void TowheeIntegratorEventManager::removeListener(IAPIIntegratorListener *listener) {
printf("TowheeIntegratorEventManager::removeListener() NOT implemented yet.\n"); fflush(stdout);
    }

    /*
     * stepStartedNotify()
     */
    void TowheeIntegratorEventManager::stepStartedNotify() {
        for(int i = 0; i < mListeners.size(); i++) {
            mListeners.at(i)->integratorStepStarted(NULL);
        }
    }
    /*
     * stepCompletedNotify()
     */
    void TowheeIntegratorEventManager::stepCompletedNotify() {
        for(int i = 0; i < mListeners.size(); i++) {
            mListeners.at(i)->integratorStepFinished(NULL);
        }
    }

}
