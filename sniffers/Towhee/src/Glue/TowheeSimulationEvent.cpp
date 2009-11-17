/*
 *  TowheeSimulationEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationEvent::TowheeSimulationEvent(IAPISimulation *sim) {
        mSim = sim;
    }

    /*
     * getSimulation()
     */
    IAPISimulation *TowheeSimulationEvent::getSimulation() {
        return mSim;
    }


}
