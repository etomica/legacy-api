/*
 *  GlotzillaSimulationAtomTypeEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationAtomTypeEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationAtomTypeEvent::GlotzillaSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType) :
                                                         GlotzillaSimulationEvent(sim) {
        mAtomType = atomType;
    }

    /*
     * getAtomType()
     */
    IAPIAtomType *GlotzillaSimulationAtomTypeEvent::getAtomType() {
        return mAtomType;
    }


}
