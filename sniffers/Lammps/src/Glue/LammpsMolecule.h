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

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsMolecule : public virtual IAPIMolecule {

        public:

            LammpsMolecule(int nIndex);

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

        private:
            LammpsAtomList *mAtoms;
            int mIndex;
            int nativeMoleculeID;

    };
}
#endif
