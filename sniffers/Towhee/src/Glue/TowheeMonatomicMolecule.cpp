/*
 *  TowheeMonatomicMolecule.cpp
 *  API Glue
 *
 */

#include "TowheeMonatomicMolecule.h"
#include "TowheeAtomList.h"

namespace towheesnifferwrappers
{

    TowheeMonatomicMolecule:: TowheeMonatomicMolecule(IAPISpecies *species) {
        mSpecies = species;
        mAtoms = new TowheeAtomList();
    }

    /*
     * addChildAtom()
     */
    void TowheeMonatomicMolecule::addChildAtom(IAPIAtom *atom) {
//        if(mAtoms->getAtomCount() == 0) {
            mAtoms->addChildAtom(atom);
            atom->setIndex(mAtoms->getAtomCount()-1);
//        }
//        else {
//printf("TowheeMonatomicMolecule::addChildAtom -> The monatomic molecule already has a child atom.\n"); fflush(stdout);
//        }
    }

    /*
     * removeChildAtom()
     */
    void TowheeMonatomicMolecule::removeChildAtom(IAPIAtom *atom) {
        // do not implement this method
    }

    /*
     * getChildList()
     */
    IAPIAtomList *TowheeMonatomicMolecule::getChildList() {
        return mAtoms;
    }

}
