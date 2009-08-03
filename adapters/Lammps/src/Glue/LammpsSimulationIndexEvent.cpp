/*
 *  LammpsSimulationIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationIndexEvent.h"

namespace lammpswrappers
{

    LammpsSimulationIndexEvent::LammpsSimulationIndexEvent(IAPISimulation *sim, int idx) :
                                                         LammpsSimulationEvent(sim) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int LammpsSimulationIndexEvent::getIndex() {
        return mIndex;
    }


}
