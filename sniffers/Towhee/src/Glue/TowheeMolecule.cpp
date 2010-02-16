/*
 *  TowheeMolecule.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeMolecule.h"

namespace towheesnifferwrappers
{

    TowheeMolecule::TowheeMolecule(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getIndex()
     */
    int TowheeMolecule::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void TowheeMolecule::setIndex(int index) {
        mIndex = index;
    }

    /*
     * addChildAtom
     */
    void TowheeMolecule::addChildAtom(IAPIAtom *atom) {
        printf("ERROR : TowheeMolecule::addChildAtom(IAPIAtom *) is not implemented.\n");
    }

    /*
     * removeChildAtom
     */
    void TowheeMolecule::removeChildAtom(IAPIAtom *atom) {
        printf("ERROR : TowheeMolecule::removeChildAtom(IAPIAtom *) is not implemented.\n");
    }

    /*
     * getChildList
     */
    IAPIAtomList *TowheeMolecule::getChildList() {
        printf("TowheeMolecule::getChildList() is not implemented.\n");
    }

    /*
     * getType()
     */
    IAPISpecies *TowheeMolecule::getType() {
        return mSpecies;
    }

    /*
     * setBox()
     */
    void TowheeMolecule::setBox(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeMolecule::getBox() {
        return mBox;
    }


}
