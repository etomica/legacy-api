/*
 *  TowheeSimulationSpeciesEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationSpeciesEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationSpeciesEvent::TowheeSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species) :
                                                         TowheeSimulationEvent(sim) {
        mSpecies = species;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSimulationSpeciesEvent::getSpecies() {
        return mSpecies;
    }


}
