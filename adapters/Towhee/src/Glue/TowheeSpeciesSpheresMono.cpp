/*
 *  TowheeSpeciesSpheresSpheresMono.cpp
 *  API Glue
 *
 */

#include "TowheeSpeciesSpheresMono.h"
#include "TowheeAtom.h"
#include "TowheeMonatomicMolecule.h"

namespace towheewrappers
{

    TowheeSpeciesSpheresMono::TowheeSpeciesSpheresMono(TowheeSimulation *sim, IAPIAtomType *at,
                                                       IAPIBoundary *boundary) {
        mAtomType = at;
        mTypeList.push_back(mAtomType);
        mAtomIDMgr = sim->getAtomIDMgr();
        mMoleIDMgr = sim->getMoleculeIDMgr();
        mBoundary = boundary;
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *TowheeSpeciesSpheresMono::makeMolecule() {
        IAPIAtom *atom = new TowheeAtom(mAtomType, mAtomIDMgr->getNextIndex(), mBoundary);
        IAPIMolecule *mole = new TowheeMonatomicMolecule(this, mMoleIDMgr->getNextIndex());
        atom->setParent(mole);
        mole->addChildAtom(atom);
        return mole;
    }

}
