/*
 *  TowheeMoleculeList.h
 *  API Glue
 *
 */

#ifndef TOWHEE_MOLECULE_LIST_WRAPPER_H
#define TOWHEE_MOLECULE_LIST_WRAPPER_H

#include <vector>

#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeMoleculeList : public virtual IAPIMoleculeList {
        public:
            TowheeMoleculeList();

            // API Compliance
            int getMoleculeCount();			
            IAPIMolecule *getMolecule(int);

            // Non-API methods
            void addMolecule(IAPIMolecule *);
            void removeMolecule(IAPIMolecule *);
            void clear();

        protected:
            std::vector<IAPIMolecule *> mMolecule;
    };
}
#endif
