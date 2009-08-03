/*
 *  GlotzillaMoleculeList.h
 *  API Glue
 *
 */

#ifndef GLOTZ_MOLELIST_WRAPPER_H
#define GLOTZ_MOLELIST_WRAPPER_H

#include <vector>

#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaMoleculeList is a list that holds molecules.  There are
      * methods to add/remove molecules to/from the list, get the size of the
      * molecule list and get molecules contained in the list.
      */
    class GlotzillaMoleculeList : public virtual IAPIMoleculeList {
        public:
            /**
              * Constructor that creates a molecule list.
              */
            GlotzillaMoleculeList();
            virtual ~GlotzillaMoleculeList();

            // API Compliance
            /**
              * @return Returns the number of molecules in the molecule list.
              */
            int getMoleculeCount();
            /**
              * Used to get a molecule from the molecule list.
              * @param i The position of the molecule in the molecule list to
              *          get.  The position indices start at 0.
              * @return Returns the number of molecules in the molecule list.
              */
            IAPIMolecule *getMolecule(int i);

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
            std::vector<IAPIMolecule *> mMole;
    };
}
#endif
