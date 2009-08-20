/*
 *  TowheeSpeciesManager.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "TowheeSpeciesManager.h"

namespace towheewrappers
{

    /*
     * removeSpecies()
     */
    void TowheeSpeciesManager::removeSpecies(IAPISpecies *species) {
printf("WARNING : TowheeSpeciesManager::removeSpecies() not implemented.\n"); fflush(stdout);
    }

    /*
     * addSpecies()
     */
    void TowheeSpeciesManager::addSpecies(IAPISpecies *species) {
        mSpecies.push_back(species);
    }

    /*
     * boxAddedNotify()
     */
    void TowheeSpeciesManager::boxAddedNotify(IAPIBox *box) {
printf("WARNING : TowheeSpeciesManager::boxAddedNotify() not implemented.\n"); fflush(stdout);
    }

    /*
     * getSpeciesCount()
     */
    int TowheeSpeciesManager::getSpeciesCount() {
        return mSpecies.size();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSpeciesManager::getSpecies(int index) {
        return mSpecies.at(index);
    }



}
