/*
 *  TowheeMolecule.cpp
 *  API Glue
 *
 */

#include "TowheeMolecule.h"

namespace towheesnifferwrappers
{

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
    }

    /*
     * removeChildAtom
     */
    void TowheeMolecule::removeChildAtom(IAPIAtom *atom) {
    }

    /*
     * getChildList
     */
    IAPIAtomList *TowheeMolecule::getChildList() {
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
