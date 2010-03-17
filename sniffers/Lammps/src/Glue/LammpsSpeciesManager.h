/*
 *  LammpsSpeciesManager.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPECIESMGR_WRAPPER_H
#define LAMMPS_SPECIESMGR_WRAPPER_H

#include <vector>

#include "IAPIBox.h"
#include "IAPISpecies.h"
#include "IAPIAtomType.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsSpeciesManager {

        public:
	    void removeSpecies(IAPISpecies *delSpecies);
	    void addSpecies(IAPISpecies *newSpecies);
	    void boxAddedNotify(IAPIBox *box);
            virtual int getSpeciesCount();
            virtual IAPISpecies *getSpecies(int index);

        private:
            std::vector<IAPISpecies *> speciesList;
            std::vector<IAPIBox *> boxList;
    };

}

#endif
