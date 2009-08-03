/*
 *  GlotzillaSimulationSpeciesIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationSpeciesIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationSpeciesIndexEvent::GlotzillaSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *box, int idx) :
                                                         GlotzillaSimulationSpeciesEvent(sim, box) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int GlotzillaSimulationSpeciesIndexEvent::getIndex() {
        return mIndex;
    }


}
