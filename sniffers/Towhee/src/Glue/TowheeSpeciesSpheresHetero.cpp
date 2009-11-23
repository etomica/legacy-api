/*
 *  TowheeSpeciesSpheresSpheresHetero.cpp
 *  API Glue
 *
 */

#include "TowheeSpeciesSpheresHetero.h"
#include "TowheeAtom.h"
#include "TowheeMonatomicMolecule.h"

namespace towheesnifferwrappers
{

    TowheeSpeciesSpheresHetero::TowheeSpeciesSpheresHetero(TowheeSimulationSniffer *sim) :
                                                   TowheeSpecies(sim) {
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *TowheeSpeciesSpheresHetero::makeMolecule() {
printf("TowheeSpeciesSpheresHetero::makeMolecule() NOT implemented.\n"); fflush(stdout);
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *TowheeSpeciesSpheresHetero::makeMolecule(int mID) {
        IAPIMolecule *mole = new TowheeMonatomicMolecule(this, mID);
        for(int i = 0; i < getAtomTypeCount(); i++) {
            IAPIAtom *atom = new TowheeAtom(getAtomType(i), mSim->getAtomIDMgr()->getNextIndex());
            atom->setParent(mole);
            mole->addChildAtom(atom);
        }

        return mole;
    }

    /*
     * addAtomType()
     */
    void TowheeSpeciesSpheresHetero::addAtomType(IAPIAtomType *atomType) {
        mTypeList.push_back(atomType);
    }

}
