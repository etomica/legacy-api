/*
 *  TowheeMoleculeList.h
 *  API Glue
 *
 */

#ifndef TOWHEE_MOLELIST_WRAPPER_H
#define TOWHEE_MOLELIST_WRAPPER_H

#include <vector>

#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeMoleculeList : public virtual IAPIMoleculeList {
        public:
            int getMoleculeCount();
            IAPIMolecule *getMolecule(int i);

            // Non-API methods
            void addMolecule(IAPIMolecule *mole);
            void clear();

        private:
            std::vector<IAPIMolecule *>mMole;
    };
}
#endif
