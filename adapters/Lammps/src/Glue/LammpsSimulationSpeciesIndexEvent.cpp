/*
 *  LammpsSimulationSpeciesIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationSpeciesIndexEvent.h"

namespace lammpswrappers
{

    LammpsSimulationSpeciesIndexEvent::LammpsSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *box, int idx) :
                                                         LammpsSimulationSpeciesEvent(sim, box) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int LammpsSimulationSpeciesIndexEvent::getIndex() {
        return mIndex;
    }


}
