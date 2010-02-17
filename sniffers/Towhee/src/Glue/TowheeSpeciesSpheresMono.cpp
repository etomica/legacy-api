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
//printf("ERROR : TowheeSpeciesSpheresMono::makeMolecule() is not implemented.\n");
printf("WARNING : TowheeSpeciesSpheresMono::makeMolecule() is implemented and should not be.\n");

        IAPIMolecule *mole = new TowheeMonatomicMolecule(this, mSim->getBox(0));
        IAPIAtom *atom = new TowheeAtom(mAtomType, mSim->getAtomIDMgr()->getNextIndex(), mole);
        mole->addChildAtom(atom);
        return mole;

    }

}
