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
            /**
              * Add a molecule to the molecule list.
              * @param mole The molecule to add to the molecule list.
              */
            void addMolecule(IAPIMolecule *mole);
            /**
              * Remove a molecule from the molecule list.
              * @param mole The molecule to remove from the molecule list.
              */
            void removeMolecule(IAPIMolecule *mole);
            /**
              * Remove all molecules from the molecule list.  The molecule
              * list will be blank after execution of the method.
              */
            void clear();

        protected:
            std::vector<IAPIMolecule *> mMolecule;
    };
}
#endif
