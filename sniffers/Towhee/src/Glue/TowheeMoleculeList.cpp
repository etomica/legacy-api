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
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *TowheeMoleculeList::getMolecule(int i) {
    }

    /*
     * addMolecule()
     */
    void TowheeMoleculeList::addMolecule(IAPIMolecule *mole) {
        mMole.push_back(mole);
    }

}
