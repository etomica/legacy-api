/*
 *  LammpsSimulationAtomTypeEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationAtomTypeEvent.h"

namespace lammpswrappers
{

    LammpsSimulationAtomTypeEvent::LammpsSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType) :
                                                         LammpsSimulationEvent(sim) {
        mAtomType = atomType;
    }

    /*
     * getAtomType()
     */
    IAPIAtomType *LammpsSimulationAtomTypeEvent::getAtomType() {
        return mAtomType;
    }


}
