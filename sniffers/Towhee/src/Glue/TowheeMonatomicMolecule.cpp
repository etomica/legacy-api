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
                     (std::vector<TowheeAtom *>atoms, IAPISpecies *species) :
                                                    TowheeMolecule(species) {
        mAtoms = new TowheeAtomList();
        for(int i = 0; i < atoms.size(); i++) {
            mAtoms->addChildAtom(atoms[i]);
            atoms[i]->setIndex(mAtoms->getAtomCount()-1);
        }

    }

//    TowheeMonatomicMolecule::TowheeMonatomicMolecule
//                                     (IAPISpecies *species, IAPIBox *box)  :
//                                        TowheeMolecule::TowheeMolecule(box) {
//        mSpecies = species;
//        mAtoms = new TowheeAtomList();
//    }

    /*
     * addChildAtom()
     */
    void TowheeMonatomicMolecule::addChildAtom(IAPIAtom *atom) {
        printf("ERROR : TowheeMonatomicMolecule::addChildAtom(IAPIAtom *) is not implemented.\n");
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
