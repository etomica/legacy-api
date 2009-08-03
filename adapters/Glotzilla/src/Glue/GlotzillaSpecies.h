/*
 *  GlotzillaSpecies.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPECIES_WRAPPER_H
#define GLOTZ_SPECIES_WRAPPER_H

#include "jni.h"

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "IAPISimulation.h"
#include "IAPISpeciesManager.h"
#include "GlotzillaInterfaceConformation.h"
#include "GlotzillaSimulation.h"

#include <vector>

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaSpecies here.
      */
    class GlotzillaSpecies : public virtual IAPISpecies {

        public:

            /**
              * Constructor for the species.  The class is purely
              * virtual and the constructor is only called by its
              * subclasses.
              * @param sim Simulations that the species belongs to.
              * @param conform The species conformation.
              * @param pd The species atom position definition.
              */
            GlotzillaSpecies(IAPISimulation *sim,
                             GlotzillaInterfaceConformation *conform);
            // API compliant methods
            /**
              * Get the specie's index.  The index is a number that
              * indicates its position in the simulation's specie list.
              * @return Returns specie's index in simulation's specie list.
              */
            virtual int getIndex();
            /**
              * Set the specie's index.  The index is a number that
              * indicates its position in the simulation's species list.
              * The list index starts at 0.
              * @param index atom types index
              */
            virtual void setIndex(int index);
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
            int getAtomTypeCount();
            /**
              * @param index index into specie's atom type list to fetch.
              * @return Returns the atom type from the atom type list for
              *         the specified index.
              */
            IAPIAtomType *getAtomType(int index);
            /**
              * Set the position of the atoms in a molecule.
              * @param molecule Molecule to initialize position of atoms.
              */
            void initializeConformation(IAPIMolecule *molecule);

            // Non-API methods
            /**
              * Add an atom type to the species atom type list used for
              * molecule creation.
              * @param type atom type to add to list.
              */
            virtual void addChildType(IAPIAtomType *type);
            /**
              * Remove an atom type from the species atom type list used for
              * molecule creation.
              * @param type atom type to remove from list.
              * @todo Current implementation checks atom type's index an
              *       removes from list if index matches.  Removes all atom
              *       types from list with same index.  What should really be
              *       removed is to complare pointers and remove if pointer
              *       is the same.
              */
            void removeChildType(IAPIAtomType *type);

        protected:
            GlotzillaInterfaceConformation *mConformation;
            std::vector<IAPIAtomType *> typeList;
            GlotzillaSimulation *mSim;

        private:
            int mIndex;
    };
}

#endif
