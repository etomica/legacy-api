/*
 *  LammpsSimulationEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationEvent.h"

namespace lammpswrappers
{

    LammpsSimulationEvent::LammpsSimulationEvent(IAPISimulation *sim) {
        mSim = sim;
    }

    /*
     * getSimulation()
     */
    IAPISimulation *LammpsSimulationEvent::getSimulation() {
        return mSim;
    }


}
