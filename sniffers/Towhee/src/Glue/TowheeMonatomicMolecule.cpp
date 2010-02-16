/*
 *  TowheeMonatomicMolecule.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeMonatomicMolecule.h"
#include "TowheeAtomList.h"

namespace towheesnifferwrappers
{

    TowheeMonatomicMolecule::TowheeMonatomicMolecule
                                     (IAPISpecies *species, IAPIBox *box)  :
                                        TowheeMolecule::TowheeMolecule(box) {
        mSpecies = species;
        mAtoms = new TowheeAtomList();
    }

    /*
     * addChildAtom()
     */
    void TowheeMonatomicMolecule::addChildAtom(IAPIAtom *atom) {
        printf("WARNING : TowheeMonatomicMolecule::addChildAtom(IAPIAtom *) is implemented but should NOT be.\n");
        mAtoms->addChildAtom(atom);
        atom->setIndex(mAtoms->getAtomCount()-1);
    }

    /*
     * removeChildAtom()
     */
    void TowheeMonatomicMolecule::removeChildAtom(IAPIAtom *atom) {
        printf("ERROR : TowheeMonatomicMolecule::removeChildAtom(IAPIAtom *) is not implemented.\n");
    }

    /*
     * getChildList()
     */
    IAPIAtomList *TowheeMonatomicMolecule::getChildList() {
        return mAtoms;
    }

}
