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
        species->setIndex(mSpecies.size()-1);
        // perform for all boxs in simulation
        for(int i = 0; i < mBoxList.size(); i++)
            mBoxList.at(i)->addSpeciesNotify(species);
    }

    /*
     * boxAddedNotify()
     */
    void TowheeSpeciesManager::boxAddedNotify(IAPIBox *box) {
        mBoxList.push_back(box);
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
