/*
 *  IAPIMolecule.h
 *  API Glue
 *
 */

#ifndef API_IMOLECULE_WRAPPER_H
#define API_IMOLECULE_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPISpecies.h"

namespace molesimAPI
{

    class IAPIMolecule {

        public:
            /**
              * @return Returns this molecules's index, which is its place in
              * the box's molecule list which the molecule is a part of.
              */
            virtual int getIndex() = 0;
            /**
              * A molecule's index is its place in the box's molecule list
              * which the molecule is a part of.
              * @param index The molecule's index
              */
            virtual void setIndex(int index) = 0;
            /**
              * Adds the given atom as a child of this Molecule.  The given
              * child atom should be parentless when this method is called.
              * @param atom Atom to add to molecule
              */
            virtual void addChildAtom(IAPIAtom *) = 0;
            /**
              * Removes the given atom as a child of this Molecule.
              * @param atom Atom to remove from molecule
              */
            virtual void removeChildAtom(IAPIAtom *) = 0;
            /**
              *  @return Returns the atoms that belong to the molecule in a
              *          list.
              */
            virtual IAPIAtomList *getChildList() = 0;
            /**
              * @return Returns the species of the molecule.
              */
            virtual IAPISpecies *getType() = 0;

    };
}
#endif
