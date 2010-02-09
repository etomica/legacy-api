/*
 *  LammpsSpeciesManager.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSpeciesManager.h"

namespace lammpssnifferwrappers
{

    /*
     * addSpecies
     */
    void LammpsSpeciesManager::addSpecies(IAPISpecies *newSpecies) {
        speciesList.push_back(newSpecies);
        newSpecies->setIndex(speciesList.size() - 1);
printf("   new species index : %d\n", newSpecies->getIndex()); fflush(stdout);

        for(int i = 0; i < boxList.size(); i++) {
            boxList[i]->addSpeciesNotify(newSpecies);
        }
    }

    /*
     * removeSpecies
     */
    void LammpsSpeciesManager::removeSpecies(IAPISpecies *delSpecies) {
        printf("WARNING : LammpsSpeciesManager::removeSpecies() is NOT implemented\n");

/*
        int index = -1;

        for(int i = 0; i < speciesList.size(); i++) {
            if(speciesList.at(i) == delSpecies) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            speciesList.erase(speciesList.begin()+index, speciesList.begin()+index+1);
            // Now need to call the rest of the species in the list to tell them
            // there index has changed.
        }
        else {
            printf("WARNING : Attempted to delete a species that is not managed by this species master.\n");
        }
*/
    }

    /*
     * boxAddedNotify
     */
    void LammpsSpeciesManager::boxAddedNotify(IAPIBox *box) {
        bool inList = false;
        for(int i = 0; i < boxList.size(); i++) {
            if(boxList[i] == box) {
                inList = true;
                break;
            }
        }
        if(!inList) {
            boxList.push_back(box);
        }
    }

    /*
     * getSpeciesCount
     */
    int LammpsSpeciesManager::getSpeciesCount() {
        return speciesList.size();
    }

    /*
     * getSpecies
     */
    IAPISpecies *LammpsSpeciesManager::getSpecies(int index) {
        if(index < speciesList.size()) {
            return speciesList.at(index);
        }
        else {
            printf("ERROR : LammpsSpeciesManager.getSpecies() incorrect index passed in.\n");
            return NULL;
        }
    }

}

