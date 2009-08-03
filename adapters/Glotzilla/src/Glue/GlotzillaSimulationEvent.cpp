/*
 *  GlotzillaSimulationEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationEvent::GlotzillaSimulationEvent(IAPISimulation *sim) {
        mSim = sim;
    }

    /*
     * getSimulation()
     */
    IAPISimulation *GlotzillaSimulationEvent::getSimulation() {
        return mSim;
    }


}
