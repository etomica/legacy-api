/*
 *  LammpsAtomList.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMLIST_WRAPPER_H
#define LAMMPS_ATOMLIST_WRAPPER_H

#include <vector>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtomList : public virtual IAPIAtomList {
        public:
            LammpsAtomList();

            // API Compliance
            int getAtomCount();			
            IAPIAtom *getAtom(int);

            // Non-API methods
            /**
              * Add an atom to the atom list.
              * @param atom The atom to add to the atom list.
              */
            void addAtom(IAPIAtom *);
            /**
              * Remove an atom from the atom list.
              * @param atom The atom to remove from the atom list.
              */
            void removeAtom(IAPIAtom *);
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
