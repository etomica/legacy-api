/*
 *  LammpsSimulationSpeciesEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationSpeciesEvent.h"

namespace lammpswrappers
{

    LammpsSimulationSpeciesEvent::LammpsSimulationSpeciesEvent(IAPISimulation *sim, IAPISpecies *species) :
                                                         LammpsSimulationEvent(sim) {
        mSpecies = species;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *LammpsSimulationSpeciesEvent::getSpecies() {
        return mSpecies;
    }


}
