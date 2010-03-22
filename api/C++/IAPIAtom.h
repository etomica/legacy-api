/*
 *  IAPIAtom.h
 *  API Glue
 *
 */

#ifndef API_IATOM_WRAPPER_H
#define API_IATOM_WRAPPER_H

#include "IAPIVectorMutable.h"

namespace molesimAPI
{

    class IAPIBox;
    class IAPIMolecule;
    class IAPIAtomType;

    class IAPIAtom {

        public:
            /**
              * @return Returns this atom's index, which is its place in the
              *         parent molecule's list of child atoms.
              */
            virtual int getIndex() = 0;
            /**
              * Set the index, which is the atom's place in the parent
              * molecule's list of child atoms.
              * @param The atoms index
              */
            virtual void setIndex(int index) = 0;
            /**
              * Each box has a list of atom's that it holds.  The atom holds
              * a local copy of that value.
              * @param index The atom's leaf index. 
              */
            virtual void setLeafIndex(int newLeafIndex) = 0;
            /**
              * @return newLeafIndex Each box has a list of atom's that it
              *                      holds.  Returns the atom's place in that
              *                      list.
              */
            virtual int getLeafIndex() = 0;
            /**
              * An atom may be part of a molecule.  The atom holds a local
              * copy of that molecule.
              * @param newParent The atom's parent molecule.
              */
            virtual void setParent(IAPIMolecule *newParent) = 0;
            /**
              * An atom may be part of a molecule.  The atom holds a local
              * copy of that molecule.
              * @return Returns the molecule that the atom is part of.
              */
            virtual IAPIMolecule *getParentGroup() = 0;
            /**
              * @return Returns the atom type of this atoms, which holds
              *         properties in common with other atoms of the same
              *         type.
              */
            virtual IAPIAtomType *getType() = 0;
            /**
              * @return Returns a vector holding the position of the atom.
              *         The position of the atom can be changed by changing
              *         the values of the returned vector.
              */
            virtual IAPIVectorMutable *getPosition() = 0;
    };
}
#endif
