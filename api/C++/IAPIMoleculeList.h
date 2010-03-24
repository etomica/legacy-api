/*
 *  IAPIMoleculeList.h
 *  API Glue
 *
 */

#ifndef API_IMOLECULELIST_WRAPPER_H
#define API_IMOLECULELIST_WRAPPER_H

#include "IAPIMolecule.h"

namespace molesimAPI
{

    class IAPIMoleculeList {

        public:

            // API Compliance
            /**
              * @return Returns the number of molecules in the molecule list.
              */
            virtual int getMoleculeCount() = 0;
            /**
              * Used to get a molecule from the molecule list.
              * @param i The position of the molecule in the molecule list to
              *          get.  The position indices start at 0.
              * @return Returns the molecule in the molecule list at the
              *         given index.
              */
            virtual IAPIMolecule *getMolecule(int i) = 0;

    };
}
#endif
