/*
 *  LammpsMolecule.h
 *  API Glue
 *
 */

#ifndef LAMMPS_MOLECULE_WRAPPER_H
#define LAMMPS_MOLECULE_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPISpecies.h"
#include "IAPIMolecule.h"
#include "IAPISimulation.h"
#include "LammpsAtom.h"
#include "LammpsAtomList.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsMolecule : public virtual IAPIMolecule {

        public:

            LammpsMolecule(IAPISimulation *sim, IAPISpecies *at);

            // API Compliance
            int getIndex();
            void setIndex(int index);
            virtual void addChildAtom(IAPIAtom *atom);
            virtual void removeChildAtom(IAPIAtom *atom);
            virtual IAPIAtomList *getChildList();
            IAPISpecies *getType();

            // Non-API methods
            void setVelocity(IAPIVector *velocity);

        protected:
            IAPISpecies *mAtomType;
            LammpsSimulation *mSim;

        private:
            LammpsAtomList *mAtoms;
            int mIndex;
            char *nativeMoleculeID;

    };
}
#endif
