/*
 *  IndexManager.cpp
 *  API Glue
 *
 *
 */

#include "IndexManager.h"

namespace towheesnifferwrappers
{

    IndexManager::IndexManager(int startsAt) {
        currentIndex = startsAt;
    }

    /*
     * getNextIndex()
     */
    int IndexManager::getNextIndex() {
        currentIndex++;
        return currentIndex-1;
    }

}
