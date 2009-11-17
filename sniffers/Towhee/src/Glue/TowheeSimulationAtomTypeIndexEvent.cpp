/*
 *  TowheeSimulationAtomTypeIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationAtomTypeIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationAtomTypeIndexEvent::TowheeSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx) :
                                                         TowheeSimulationAtomTypeEvent(sim, atomType) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int TowheeSimulationAtomTypeIndexEvent::getIndex() {
        return mIndex;
    }


}
