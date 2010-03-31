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

namespace lammpswrappers
{

    /**
      *  LammpsSpeciesManager manages the species that are part of a
      *  simulation.
      */
    class LammpsSpeciesManager {

        public:
            /**
              * This method is not implemented.
              */
	    void removeSpecies(IAPISpecies *delSpecies);
            /**
              * Adds the given species to this species manager's species
              * list.
              * @param newSpecies Species to add to species manager.
              */
	    void addSpecies(IAPISpecies *newSpecies);
            /**
              * Called (hopefully by the simulation automatically) when a
              * box is added to the simulation.  Keeps a handle to the box
              * so it can notify the box when a species is added.
              * @param box The box added to the simulation.
              * @todo This method is not implemented.
              */
	    void boxAddedNotify(IAPIBox *box);
            /**
              * @return Returns the number of species held by this species
              *         manager.
              */
            virtual int getSpeciesCount();
            /**
              * @param index Index into specie manager's species list.
              *              Indices start at 0.
              * @return Returns the species held in the specie manager's
              *         specie list at the given index.
              */
            virtual IAPISpecies *getSpecies(int index);

        private:
            std::vector<IAPISpecies *> speciesList;
            std::vector<IAPIBox *> boxList;
    };

}

#endif
