/*
 *  LammpsMoleculeList.cpp
 *  API Glue
 *
 */

#include "LammpsMoleculeList.h"

namespace lammpswrappers
{

    LammpsMoleculeList::LammpsMoleculeList() {
    }

    /*
     * getMoleculeCount()
     */
    int LammpsMoleculeList::getMoleculeCount() {
        return mMolecule.size();
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *LammpsMoleculeList::getMolecule(int i) {
        return mMolecule.at(i);
    }

    /*
     * addMolecule()
     */
    void LammpsMoleculeList::addMolecule(IAPIMolecule *mole) {
        mMolecule.push_back(mole);
    }

    /*
     * removeMolecule()
     */
    void LammpsMoleculeList::removeMolecule(IAPIMolecule *mole) {

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
            printf("WARNING : Attempted to delete a molecule that is not in the molecule list.\n");
        }

    }

    /*
     * clear()
     */
    void LammpsMoleculeList::clear() {
        mMolecule.erase(mMolecule.begin(), mMolecule.end());
    }

}
