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
printf("ERROR : TowheeSpeciesSpheresHetero::makeMolecule() is not implemented.\n");
/*
        IAPIMolecule *mole = new TowheeMonatomicMolecule(this);
        for(int i = 0; i < getAtomTypeCount(); i++) {
            IAPIAtom *atom = new TowheeAtom(getAtomType(i), mSim->getAtomIDMgr()->getNextIndex(), mole);
            mole->addChildAtom(atom);
        }

        return mole;
*/

    }

    /*
     * addAtomType()
     */
    void TowheeSpeciesSpheresHetero::addAtomType(IAPIAtomType *atomType) {
        mTypeList.push_back(atomType);
    }

}
