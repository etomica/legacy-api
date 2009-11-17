/*
 *  TowheeSimulationAtomTypeEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationAtomTypeEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationAtomTypeEvent::TowheeSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType) :
                                                         TowheeSimulationEvent(sim) {
        mAtomType = atomType;
    }

    /*
     * getAtomType()
     */
    IAPIAtomType *TowheeSimulationAtomTypeEvent::getAtomType() {
        return mAtomType;
    }


}
