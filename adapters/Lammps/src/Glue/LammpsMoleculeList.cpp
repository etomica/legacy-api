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
    void LammpsMoleculeList::addMolecule(IAPIMolecule *atom) {
        mMolecule.push_back(atom);
    }

    /*
     * removeMolecule()
     */
    void LammpsMoleculeList::removeMolecule(IAPIMolecule *atom) {

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
    void LammpsMoleculeList::clear() {
        mMolecule.erase(mMolecule.begin(), mMolecule.end());
    }

}
