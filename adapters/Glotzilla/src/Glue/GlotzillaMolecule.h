/*
 *  GlotzillaMolecule.h
 *  API Glue
 *
 */

#ifndef GLOTZ_MOLECULE_WRAPPER_H
#define GLOTZ_MOLECULE_WRAPPER_H

#include <glotzmd.h>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPISimulation.h"
#include "IAPISpecies.h"
#include "IAPIMolecule.h"
#include "GlotzillaAtom.h"
#include "GlotzillaAtomList.h"
#include "GlotzillaSimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaMolecule is a superclass.  It represents a physical
      * molecule of a species that has atom(s).  All subclasses will hold a
      * Glotzilla native molecule, the type of which will be determined by
      * the specific kind of the molecule subclass
      * (polyer, particle, etc...).
      */
    class GlotzillaMolecule : public virtual IAPIMolecule {

        public:
            /**
              * Constructor that generates a molecule of the given species.
              * The class is purely virtual so the constructor is only
              * called by its subclasses.
              * @param sim Simulation that the molecule belongs to.
              * @param species The species for this molecule.
              */
            GlotzillaMolecule(IAPISimulation *sim, IAPISpecies *species);

            // API Compliance

            /**
              * @return Returns this molecules's index, which is its place in
              * the parent AtomGroup's list of molecules (which is held by
              * the box).
              * @todo This method is not implemented correctly.  Currently,
              *       it is returning the atom's atom type index.
              */
            virtual int getIndex();
            /**
             * This method is not implemented.  When the molecule is added to
             * the native Glotzilla simulation, the native Glotzilla
             * simulation assigns an index to the molecule and holds that
             * index.  The Glotzilla implementation makes this method
             * unnecessary.
             * @param index molecule's new index
             */
            virtual void setIndex(int);
            /**
              * Adds the given atom as a child of this Molecule.  The given
              * child atom should be parentless when this method is called.
              * @param atom Atom to add to molecule
              */
            virtual void addChildAtom(IAPIAtom *atom) = 0;
            /**
              * Removes the given atom as a child of this Molecule.
              * @param atom Atom to remove from molecule
              */
            virtual void removeChildAtom(IAPIAtom *atom) = 0;
            /**
              *  @return Returns the atoms that belong to the molecule in a
              *          list.
              */
            virtual IAPIAtomList *getChildList() = 0;
            /**
              * @return Returns the species of the molecule.
              */
            virtual IAPISpecies *getType();

           // Non-API Methods
           /**
             * WARNING : This method should not be called outside of the
             *           glue layer implementation.
             * @return Returns the Glotzilla native object that this
             *         instance is holding.  The type of the Glotzilla
             *         native object is dependent on this instances
             *         subclass.
             */
           virtual glotzmd::Particle *getGlotzParticle() = 0;

        protected:
            GlotzillaSimulation *mSim;
            IAPISpecies *mSpecies;
            // mAtomList is not always valid and should only be
            // used as a return vehicle for getChildList.
            GlotzillaAtomList *mAtomList;

    };
}
#endif
