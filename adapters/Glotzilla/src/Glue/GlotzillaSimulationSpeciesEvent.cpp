/*
 *  GlotzillaSimulationSpeciesEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationSpeciesEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationSpeciesEvent::GlotzillaSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species) :
                                                         GlotzillaSimulationEvent(sim) {
        mSpecies = species;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *GlotzillaSimulationSpeciesEvent::getSpecies() {
        return mSpecies;
    }


}
