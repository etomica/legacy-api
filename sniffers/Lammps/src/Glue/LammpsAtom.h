/*
 *  LammpsAtom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOM_WRAPPER_H
#define LAMMPS_ATOM_WRAPPER_H

#include "IAPIAtomKinetic.h"
#include "IAPIAtom.h"
#include "IAPIMolecule.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsAtom : public virtual IAPIAtom, public virtual IAPIAtomKinetic {

        public:
            LammpsAtom(LammpsSimulation *sim, IAPIAtomType *at, IAPIMolecule *mole, int nIndex);

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
            IAPIVectorMutable *getForce();
            int getNativeIndex();

        private:
            void init(LammpsSimulation *sim, IAPIAtomType *at, IAPIMolecule *mole, int nIndex);

            // atoms are tagged starting at 1 in Lammps.  Our leaf index
            // starts at 0.  So, when using mLeafIndex to access Lammps
            // data arrays, will need to add 1 to index.
            int mLeafIndex;
            IAPIVectorMutable *mPosition;
            IAPIVectorMutable *mVel;
            IAPIVectorMutable *mForce;
            IAPIAtomType *mAtomType;
            LammpsSimulation *mSim;
            IAPIMolecule *parent;
            int mIndex;
            int nativeIndex;

    };
}
#endif
