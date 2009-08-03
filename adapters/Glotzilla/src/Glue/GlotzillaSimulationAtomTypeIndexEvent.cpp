/*
 *  GlotzillaSimulationAtomTypeIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationAtomTypeIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationAtomTypeIndexEvent::GlotzillaSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx) :
                                                         GlotzillaSimulationAtomTypeEvent(sim, atomType) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int GlotzillaSimulationAtomTypeIndexEvent::getIndex() {
        return mIndex;
    }


}
