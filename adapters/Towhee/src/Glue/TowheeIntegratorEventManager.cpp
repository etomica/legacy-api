/*
 *  TowheeIntegratorEventManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeIntegratorEventManager.h"

namespace towheewrappers
{

    /*
     * addListener
     */
    void TowheeIntegratorEventManager::addListener(IAPIIntegratorListener *newListener) {
printf("TowheeIntegratorEventManager::addListener() NOT implemented yet.\n"); fflush(stdout);
//        mListeners.push_back(dynamic_cast<TowheeIntegratorListenerNative *>(newListener));
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
printf("TowheeIntegratorEventManager::stepStartedNotify() NOT implemented yet.\n"); fflush(stdout);
//        for(int i = 0; i < mListeners.size(); i++) {
//            mListeners.at(i)->integratorStepStarted(NULL);
//        }
    }
    /*
     * stepCompletedNotify()
     */
    void TowheeIntegratorEventManager::stepCompletedNotify() {
printf("TowheeIntegratorEventManager::stepCompletedNotify() NOT implemented yet.\n"); fflush(stdout);
//        for(int i = 0; i < mListeners.size(); i++) {
//            mListeners.at(i)->integratorStepFinished(NULL);
//        }
    }

}
