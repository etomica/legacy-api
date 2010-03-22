/*
 *  IAPIAtomList.h
 *  API Glue
 *
 */

#ifndef API_IATOMLIST_WRAPPER_H
#define API_IATOMLIST_WRAPPER_H

#include "IAPIAtom.h"

namespace molesimAPI
{

    /**
      * IAPIAtomList is a list that holds atoms.  There are methods to get
      * the size of the atom list and get atoms contained in the list.
      */
    class IAPIAtomList {

        public:

            // API Compliance
            /**
              * @return Returns the number of atoms in the atom list.
              */
            virtual int getAtomCount() = 0;
            /**
              * Used to get an atom from the atom list.
              * @param i The position of the atom in the atom list to get.
              *          The position indices start at 0.
              * @return Returns the atom in the atom list at the specified
              *         location.
              */
            virtual IAPIAtom *getAtom(int) = 0;

    };
}
#endif
