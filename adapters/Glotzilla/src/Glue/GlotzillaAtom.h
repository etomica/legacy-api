/*
 *  GlotzillaAtom.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOM_WRAPPER_H
#define GLOTZ_ATOM_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomKinetic.h"
#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "GlotzillaSimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtom is an atom the represents a physical atom with
      * a position and velocity.  It holds a Glotzilla native atom
      * (glotzmd::Bead) where many of the atoms properties are stored.
      */
    class GlotzillaAtom : public virtual IAPIAtom,
                          public virtual IAPIAtomPositioned,
                          public virtual IAPIAtomKinetic {

        public:
            /**
              * Constructor that generates an atom with position set to
              * (0,0,0).  The constructor sets its atom type to a new
              * instance of GlotzillaAtomType (default ctor).  The
              * atom holds a new instance of a glotzmd::Bead.
              * @param sim Simulation that the atom belongs to.
              */
            GlotzillaAtom(IAPISimulation *sim);
            /**
              * Constructor that generates an atom with position set to
              * (0,0,0).  The constructor sets its atom type to the
              * atom type passed in.  The atom holds a new instance of a
              * glotzmd::Bead.
              * @param sim Simulation that the atom belongs to.
              * @param at The atom type for this atom.
              */
            GlotzillaAtom(IAPISimulation *sim, IAPIAtomType *at);
            /**
              * Constructor that generates an atom with position set to
              * the values that are passed in.  The constructor sets
              * its atom type to a new instance of GlotzillaAtomType
              * (default ctor).  The atom holds a new instance of a
              * glotzmd::Bead.
              * @param sim Simulation that the atom belongs to.
              * @param x The x position of this atom.
              * @param y The y position of this atom.
              * @param z The z position of this atom.
              */
            GlotzillaAtom(IAPISimulation *sim, double x, double y, double z);
            /**
              * Constructor that generates an atom with position set to
              * the values that are passed in.  The constructor sets
              * its atom type to the atom type passed in.
              * @param sim Simulation that the atom belongs to.
              * @param x The x position of this atom.
              * @param y The y position of this atom.
              * @param z The z position of this atom.
              * @param at The atom type for this atom.
              * @todo REMOVE THIS CTOR, USE THE VECTOR CTOR
              */
            GlotzillaAtom(IAPISimulation *sim, double x, double y, double z,
                          IAPIAtomType *at);
            /**
              * Constructor that generates an atom with position set to
              * the values passed in as a vector.  The constructor sets
              * its atom type to a new instance of GlotzillaAtomType
              * (default ctor).  The atom holds a new instance of a
              * glotzmd::Bead.
              * @param sim Simulation that the atom belongs to.
              * @param v A vector holding the atoms position.
              * @todo Need to check dimension of vector and set position
              *       accordingly.
              */
            GlotzillaAtom(IAPISimulation *sim, IAPIVector *v);
            /**
              * Constructor that generates an atom with position set to
              * the values passed in as a vector.  The constructor sets
              * its atom type to the atom type passed in.  The atom holds
              * a new instance of a glotzmd::Bead.
              * @param sim Simulation that the atom belongs to.
              * @param v A vector holding the atoms position.
              * @param at The atom type for this atom.
              * @todo Need to check dimension of vector and set position
              *       accordingly.
              */
            GlotzillaAtom(IAPISimulation *sim, IAPIVector *v,
                          IAPIAtomType *at);
            /**
              * Constructor that generates an atom that holds the
              * glotzmd::Bead passed in.  The constructor sets
              * its atom type to a new instance of GlotzillaAtomType
              * with its index set to glotzmd::Bead::GetType().
              * @param sim Simulation that the atom belongs to.
              * @param bead The glotzmd::Bead that this atom holds.
              */
            GlotzillaAtom(IAPISimulation *sim, glotzmd::Bead *bead);
            ~GlotzillaAtom();

            // API Compliance
            /**
              * @return Returns this atom's index, which is its place in the parent
              * molecule's list of child atoms.
              * @todo This method is not implemented correctly.  Currently,
              *       it is returning the atom's atom type index.
              */
            int getIndex();
            /**
             * This method is not implemented.  When the atom is added to
             * the native Glotzilla simulation as part of a molecule
             * (glotzmd::Particle), the particle holds it own list of
             * children and this atom's position in that list is its index.
             */
            void setIndex(int index);
            /**
             * This method is not implemented.  When the atom is added to
             * the native Glotzilla simulation, the native Glotzilla
             * simulation assigns an index to the atom and holds that index.
             * The Glotzilla implementation makes this method unnecessary.
             */
            void setLeafIndex(int newLeafIndex);
            /**
              * @return Returns this atom's leaf index, which is its place in the
              * IAPIBox list of child atoms.  Every atom has a unique leaf
              * index.  An atom's leaf index may change over the course
              * of a simulation as atoms are added and deleted from the
              * simulation.
              */
            int getLeafIndex();
            /**
              * @return Returns the position of the atom as an IAPIVector
              *         which, when modified, changed the atom's position.
              * @todo Not sure if the mutability actually works by setting
              *       the Bead's position vector.
              */
            IAPIVectorMutable *getPosition();
            /**
              * @return Returns the velocity of the atom as an IAPIVector
              *         which, when modifyed, changed the atom's velocity.
              * @todo Not sure if the mutability actually works by setting
              *       the Bead's velocity vector.
              */
            IAPIVectorMutable *getVelocity();
            /**
              * @param newParent Sets the IAPIMolecule that this atom is a
              *                  part of.
              * WARNING : This method should only be called by the atom's
              *           parent (IAPIMolecule).
              */
            void setParent(IAPIMolecule *newParent);
            /**
              * @return Returns the IAPIMolecule that this atom is a part of.
              */
            IAPIMolecule *getParentGroup();
            /**
              * @return Returns the atom type of this atoms, which holds
              *         properties in common with other atoms of the same
              *         type.
              */
            IAPIAtomType *getType();

            // Non-API methods
            /**
              * @return Returns the glotzmd::Bead that this atom is holding.
              * WARNING : This method should not be called outside of the
              *           glue layer implementation.
              */
            glotzmd::Bead *getGlotzBead();

        private:
            void init(IAPISimulation *sim, double x, double y, double z,
                      IAPIAtomType *at);

            glotzmd::Bead *glotzBead;
            GlotzillaSimulation *mSim;
            IAPIAtomType *mAtomType;
            IAPIVectorMutable *mPosition;
            IAPIVectorMutable *mVelocity;
            IAPIMolecule *parent;
            int leafIndex;

    };
}
#endif
