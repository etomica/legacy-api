/*
 *  TowheeMolecule.cpp
 *  API Glue
 *
 */

#include "TowheeMolecule.h"

namespace towheewrappers
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
