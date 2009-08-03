/*
 *  GlotzillaSimulationIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationIndexEvent::GlotzillaSimulationIndexEvent(IAPISimulation *sim, int idx) :
                                                         GlotzillaSimulationEvent(sim) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int GlotzillaSimulationIndexEvent::getIndex() {
        return mIndex;
    }


}
