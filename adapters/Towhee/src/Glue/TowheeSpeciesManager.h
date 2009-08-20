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
#include "IAPISpeciesManager.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeSpeciesManager : public virtual IAPISpeciesManager {

        public:

            // API Compliance
            void removeSpecies(IAPISpecies *species);
            void addSpecies(IAPISpecies *species);
            void boxAddedNotify(IAPIBox *box);
            int getSpeciesCount();
            IAPISpecies *getSpecies(int index);

        private:
            std::vector<IAPISpecies *>mSpecies;

    };
}

#endif
