/*
 *  TowheeSpeciesManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIESMGR_WRAPPER_H
#define TOWHEE_SPECIESMGR_WRAPPER_H

#include "IAPIBox.h"
#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPISpeciesManager.h"

#include <vector>

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      *  TowheeSpeciesManager manages the species that are part of a
      *  simulation.
      */
    class TowheeSpeciesManager : public virtual IAPISpeciesManager {

        public:
            /**
              * Adds the given species to this species manager's species
              * list.
              * @param newSpecies Species to add to species manager.
              */
	    void addSpecies(IAPISpecies *newSpecies);
            /**
              * Removes the given species to this species manager's species
              * list.
              * @param delSpecies Species to delete from species manager.
              */
	    void removeSpecies(IAPISpecies *delSpecies);
            /**
              * @param box The box added to the simulation.
              * @todo This method is not implemented.
              */
	    void boxAddedNotify(IAPIBox *box);
            /**
              * @return Returns the number of species held by this species
              *         manager.
              */
	    int getSpeciesCount();
            /**
              * @param index Index into specie manager's species list.
              *              Indices start at 0.
              * @return Returns the species held in the specie manager's
              *         specie list at the given index.
              */
	    IAPISpecies *getSpecies(int index);

        private:
            std::vector<IAPISpecies *> speciesList;
    };

}

#endif
