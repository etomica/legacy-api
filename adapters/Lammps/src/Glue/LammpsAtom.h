/*
 *  LammpsAtom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOM_WRAPPER_H
#define LAMMPS_ATOM_WRAPPER_H

#include "IAPIAtomKinetic.h"
#include "IAPIAtom.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtom : public virtual IAPIAtom, public virtual IAPIAtomKinetic {

        public:
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  The atoms postion is set to the
              * origin.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              */ 
            LammpsAtom(IAPISimulation *sim);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  The atoms postion is set to the
              * origin.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param at The atom type of this atom.
              */ 
            LammpsAtom(IAPISimulation *sim, IAPIAtomType *at);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param x The atom's initial x position
              * @param y The atom's initial y position
              * @param z The atom's initial z position
              */ 
            LammpsAtom(IAPISimulation *sim, double x, double y, double z);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param x The atom's initial x position
              * @param y The atom's initial y position
              * @param z The atom's initial z position
              * @param at The atom type of this atom.
              */ 
            LammpsAtom(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param pos A vector holding the atom's initial position.
              */ 
            LammpsAtom(IAPISimulation *sim, IAPIVector *pos);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.  Calls the atom's init method.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param pos A vector holding the atom's initial position.
              * @param at The atom type of this atom.
              */ 
            LammpsAtom(IAPISimulation *sim, IAPIVector *pos, IAPIAtomType *at);
            /**
              * LammpsAtom is an atom the represents a physical atom with
              * a position and velocity.
              * NOTE : Currently, an atom can only be bonded to one other
              *        atom.  The value is hardcoded and transferred to
              *        the native Lammps simulation.
              * @param sim The simulation that the atom is a part of.
              * @param at The atom type of this atom.
              * @param leafIndex The atom's leaf index. (See getLeafIndex)
              * Native Lammps calls :
              *   mass
              *   create_atoms
              */ 
            LammpsAtom(IAPISimulation *sim, IAPIAtomType *at, int leafIndex);

            // API Compliance
            int getIndex();
            void setIndex(int index);
            void setLeafIndex(int newGlobalIndex);
            int getLeafIndex();
            void setParent(IAPIMolecule *newParent);
            IAPIMolecule *getParentGroup();
            IAPIAtomType *getType();
            IAPIVectorMutable *getPosition();
            IAPIVectorMutable *getVelocity();

            // Non-API Method
            /**
              * @return Returns the force for the atom.  The force is
              *         determined by reaching into the native Lammps
              *         simulation.
              */
            IAPIVectorMutable *getForce();

        private:
            /**
              * Native Lammps calls :
              *   mass
              *   create_atoms
              */
            void init(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at);

            /**
              * atoms are tagged starting at 1 in Lammps.  Our leaf index
              * starts at 0.  So, when using mLeafIndex to access Lammps
              * data arrays, will need to add 1 to index.
              */
            int mLeafIndex;
            IAPIVectorMutable *mPosition;
            IAPIVectorMutable *mVel;
            IAPIVectorMutable *mForce;
            IAPIAtomType *mAtomType;
            LammpsSimulation *mSim;
            IAPIMolecule *parent;
            int mIndex;

    };
}
#endif
