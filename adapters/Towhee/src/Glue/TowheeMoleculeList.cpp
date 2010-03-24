/*
 *  TowheeMoleculeList.cpp
 *  API Glue
 *
 */

#include "TowheeMoleculeList.h"

namespace towheewrappers
{

    TowheeMoleculeList::TowheeMoleculeList() {
    }

    /*
     * getMoleculeCount()
     */
    int TowheeMoleculeList::getMoleculeCount() {
        return mMolecule.size();
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *TowheeMoleculeList::getMolecule(int i) {
        return mMolecule.at(i);
    }

    /*
     * addMolecule()
     */
    void TowheeMoleculeList::addMolecule(IAPIMolecule *mole) {
        mMolecule.push_back(mole);
    }

    /*
     * removeMolecule()
     */
    void TowheeMoleculeList::removeMolecule(IAPIMolecule *mole) {

        int index = -1;

        for(int i = 0; i < mMolecule.size(); i++) {
            if(mMolecule.at(i) == mole) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            mMolecule.erase(mMolecule.begin()+index, mMolecule.begin()+index+1);
        }
        else {
            printf("WARNING : Attempted to delete an molecule that is not in the molecule list.\n");
        }

    }

    /*
     * clear()
     */
    void TowheeMoleculeList::clear() {
        mMolecule.erase(mMolecule.begin(), mMolecule.end());
    }

}
