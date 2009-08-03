/*
 *  LammpsAtom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOM_WRAPPER_H
#define LAMMPS_ATOM_WRAPPER_H

#include "IAPIAtomKinetic.h"
#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtom : public virtual IAPIAtom, public virtual IAPIAtomPositioned,
                       public virtual IAPIAtomKinetic {

        public:
            LammpsAtom(IAPISimulation *sim);
            LammpsAtom(IAPISimulation *sim, IAPIAtomType *at);
            LammpsAtom(IAPISimulation *sim, double x, double y, double z);
            LammpsAtom(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at);
            LammpsAtom(IAPISimulation *sim, IAPIVector *pos);
            LammpsAtom(IAPISimulation *sim, IAPIVector *pos, IAPIAtomType *at);
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
            IAPIVectorMutable *getForce();

        private:
            void init(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at);

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

    };
}
#endif
