/*
 *  GlotzillaSpeciesManager.cpp
 *  API Glue
 *
 */

#include "GlotzillaSpeciesManager.h"

namespace glotzwrappers
{

    /*
     * addSpecies
     */
    void GlotzillaSpeciesManager::addSpecies(IAPISpecies *newSpecies) {
        speciesList.push_back(newSpecies);
        newSpecies->setIndex(speciesList.size() - 1);
    }

    /*
     * removeSpecies
     */
    void GlotzillaSpeciesManager::removeSpecies(IAPISpecies *delSpecies) {

        int index = -1;

        for(int i = 0; i < speciesList.size(); i++) {
            if(speciesList.at(i) == delSpecies) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            speciesList.erase(speciesList.begin()+index, speciesList.begin()+index+1);
            for(int i = index; i < speciesList.size(); i++) {
                speciesList.at(i)->setIndex(i);
            }
        }
        else {
            printf("WARNING : Attempted to delete a species that is not managed by this species master.\n");
        }

    }

    /*
     * boxAddedNotify
     */
    void GlotzillaSpeciesManager::boxAddedNotify(IAPIBox *box) {
        printf("WARNING : GlotzillaSpeciesManager::boxAddedNotify() is NOT implemented\n");
    }

    /*
     * getSpecies()
     */
    IAPISpecies *GlotzillaSpeciesManager::getSpecies(int index) {
        IAPISpecies *species = NULL;

        if(index < speciesList.size()) {
            species = speciesList.at(index);
        }
        else {
            printf("ERROR : Requested a species that does not exist : index = %d\n", index);
        }

        return species;
    }

    /*
     * getSpeciesCount()
     */
    int GlotzillaSpeciesManager::getSpeciesCount() {
        return speciesList.size();
    }

}

