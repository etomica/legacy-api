/*
 *  TowheeSpeciesSpheresSpheresMono.cpp
 *  API Glue
 *
 */

#include "TowheeSpeciesSpheresMono.h"
#include "TowheeAtom.h"
#include "TowheeMonatomicMolecule.h"

namespace towheesnifferwrappers
{

    TowheeSpeciesSpheresMono::TowheeSpeciesSpheresMono(TowheeSimulationSniffer *sim,
                                                       IAPIAtomType *at) :
                                                   TowheeSpecies(sim) {
        mAtomType = at;
        mTypeList.push_back(mAtomType);
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *TowheeSpeciesSpheresMono::makeMolecule() {
        IAPIAtom *atom = new TowheeAtom(mAtomType, mSim->getAtomIDMgr()->getNextIndex());
        IAPIMolecule *mole = new TowheeMonatomicMolecule(this);
        atom->setParent(mole);
        mole->addChildAtom(atom);
        return mole;
    }

}