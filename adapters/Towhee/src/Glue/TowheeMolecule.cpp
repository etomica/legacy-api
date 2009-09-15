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
    }

    /*
     * setIndex()
     */
    void TowheeMolecule::setIndex(int index) {
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

}
