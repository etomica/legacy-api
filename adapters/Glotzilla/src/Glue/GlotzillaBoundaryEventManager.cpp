/*
 *  GlotzillaBoundaryEventManager.cpp
 *  API  Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoundaryEventManager.h"

namespace glotzwrappers
{

    /*
     * addListener()
     */
    void GlotzillaBoundaryEventManager::addListener(IAPIBoundaryListener *listener) {
        listeners.push_back(listener);
    }

    /*
     * removeListener()
     */
    void GlotzillaBoundaryEventManager::removeListener(IAPIBoundaryListener *listener) {
printf("GlotzillaBoundaryEventManager::removeListener() is NOT implemented.\n"); fflush(stdout);
//        listeners.remove(listener);
    }

    /*
     * inflate()
     */
    void GlotzillaBoundaryEventManager::inflate(IAPIBoundary *boundary) {
printf("GlotzillaBoundaryEventManager::inflate is NOT implemented.\n"); fflush(stdout);
    }

}
