/*
 *  LammpsSimulationAtomTypeIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationAtomTypeIndexEvent.h"

namespace lammpswrappers
{

    LammpsSimulationAtomTypeIndexEvent::LammpsSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx) :
                                                         LammpsSimulationAtomTypeEvent(sim, atomType) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int LammpsSimulationAtomTypeIndexEvent::getIndex() {
        return mIndex;
    }


}
