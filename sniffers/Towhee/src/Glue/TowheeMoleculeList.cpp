/*
 *  TowheeMoleculeList.cpp
 *  API Glue
 *
 */

#include "TowheeMoleculeList.h"

namespace towheesnifferwrappers
{

    /*
     * getMoleculeCount()
     */
    int TowheeMoleculeList::getMoleculeCount() {
        return mMole.size();
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *TowheeMoleculeList::getMolecule(int i) {
        return mMole.at(i);
    }

    /*
     * addMolecule()
     */
    void TowheeMoleculeList::addMolecule(IAPIMolecule *mole) {
        mMole.push_back(mole);
    }

    /*
     * clear()
     */
    void TowheeMoleculeList::clear() {
        mMole.clear();
    }

}
