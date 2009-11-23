/*
 *  TowheeSpeciesManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIES_MGR_WRAPPER_H
#define TOWHEE_SPECIES_MGR_WRAPPER_H

#include <vector>

#include "IAPIBox.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeSpeciesManager {

        public:

            // API Compliance
            void removeSpecies(IAPISpecies *species);
            void addSpecies(IAPISpecies *species);
            void boxAddedNotify(IAPIBox *box);
            int getSpeciesCount();
            IAPISpecies *getSpecies(int index);

        private:
            std::vector<IAPISpecies *>mSpecies;
            std::vector<IAPIBox *>mBoxList;

    };
}

#endif
