/*
 *  IAPISpecies.h
 *  API Glue
 *
 */

#ifndef API_ISPECIES_WRAPPER_H
#define API_ISPECIES_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIMolecule.h"

namespace molesimAPI
{

    class IAPIAtomPositionDefinition;

    class IAPISpecies {

        public:
            /**
              * Get the specie's index.  The index is a number that
              * indicates its position in the simulation's specie list.
              * @return Returns specie's index in simulation's specie list.
              */
	    virtual int getIndex() = 0;
            /**
              * Set the specie's index.  The index is a number that
              * indicates its position in the simulation's species list.
              * The list index starts at 0.
              * @param index species index
              */
	    virtual void setIndex(int index) = 0;
            /**
              * Build a molecule of this species.
              * @return Returns the molecule constructed.
              */
	    virtual IAPIMolecule *makeMolecule() = 0;
            /**
              * @return Returns the number of atom types that a molecule of
              *         this species contains.  Note that a molecule may
              *         contain more than one atom with the same atom type,
              *         so the value returned IS NOT the number of unique
              *         atom types.
              */
            virtual int getAtomTypeCount() = 0;
            /**
              * @param index index into specie's atom type list to fetch.
              * @return Returns the atom type from the atom type list for
              *         the specified index.
              */
            virtual IAPIAtomType *getAtomType(int index) = 0;
            /**
              * Set the position of the atoms in a molecule.
              * @param molecule Molecule to initialize position of atoms.
              */
	    virtual void initializeConformation(IAPIMolecule *) = 0;

    };
}
#endif
