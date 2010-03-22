/*
 *  GlotzillaAtomList.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOMLIST_WRAPPER_H
#define GLOTZ_ATOMLIST_WRAPPER_H

#include <vector>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtomList is a list that holds atoms.  There are methods to
      * add/remove atoms to/from the list, get the size of the atom list
      * and get atoms contained in the list.
      */
    class GlotzillaAtomList : public virtual IAPIAtomList {
        public:
            /**
              * Constructor that creates an atom list.
              */
            GlotzillaAtomList();
            virtual ~GlotzillaAtomList();

            // API Compliance
            int getAtomCount();			
            IAPIAtom *getAtom(int i);

            // Non-API methods
            /**
              * Add an atom to the atom list.
              * @param atom The atom to add to the atom list.
              */
            void addAtom(IAPIAtom *atom);
            /**
              * Remove an atom from the atom list.
              * @param atom The atom to remove from the atom list.
              */
            void removeAtom(IAPIAtom *atom);
            /**
              * Remove all atoms from the atom list.  The atom list will be
              * blank after execution of the method.
              */
            void clear();

        protected:
            std::vector<IAPIAtom *> mAtom;
    };
}
#endif
