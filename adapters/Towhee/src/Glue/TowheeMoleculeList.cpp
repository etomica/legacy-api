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
    void TowheeMoleculeList::addMolecule(IAPIMolecule *atom) {
        mMolecule.push_back(atom);
    }

    /*
     * removeMolecule()
     */
    void TowheeMoleculeList::removeMolecule(IAPIMolecule *atom) {

        int index = -1;

        for(int i = 0; i < mMolecule.size(); i++) {
            if(mMolecule.at(i) == atom) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            mMolecule.erase(mMolecule.begin()+index, mMolecule.begin()+index+1);
        }
        else {
            printf("WARNING : Attempted to delete an atom that is not in the atom list.\n");
        }

    }

    /*
     * clear()
     */
    void TowheeMoleculeList::clear() {
        mMolecule.erase(mMolecule.begin(), mMolecule.end());
    }

}
