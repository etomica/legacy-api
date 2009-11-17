/*
 *  TowheeSpeciesManager.cpp
 *  API Glue
 *
 */

#include "TowheeSpeciesManager.h"

namespace towheesnifferwrappers
{

    /*
     * addSpecies
     */
    void TowheeSpeciesManager::addSpecies(IAPISpecies *newSpecies) {
        speciesList.push_back(newSpecies);
    }

    /*
     * removeSpecies
     */
    void TowheeSpeciesManager::removeSpecies(IAPISpecies *delSpecies) {
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
            for(int i = index; i < speciesList.size(); i++) {
                speciesList.at(i)->setIndex(i);
            }
        }
        else {
            printf("WARNING : Attempted to delete a species that is not managed by this species master.\n");
        }
*/
    }

    /*
     * boxAddedNotify
     */
    void TowheeSpeciesManager::boxAddedNotify(IAPIBox *box) {
        printf("WARNING : TowheeSpeciesManager::boxAddedNotify() is NOT implemented\n");
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSpeciesManager::getSpecies(int index) {
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
    int TowheeSpeciesManager::getSpeciesCount() {
        return speciesList.size();
    }

}

