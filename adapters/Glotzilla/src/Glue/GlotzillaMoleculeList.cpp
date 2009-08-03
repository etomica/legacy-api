/*
 *  GlotzillaMoleculeList.cpp
 *  API Glue
 *
 */

#include <typeinfo>

#include "GlotzillaMoleculeList.h"

namespace glotzwrappers
{

    GlotzillaMoleculeList::GlotzillaMoleculeList() {
    }

    GlotzillaMoleculeList::~GlotzillaMoleculeList() {
    }

    /*
     * getMoleculeCount()
     */
    int GlotzillaMoleculeList::getMoleculeCount() {
        return mMole.size();
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *GlotzillaMoleculeList::getMolecule(int i) {
        return mMole.at(i);
    }

    /*
     * addMolecule()
     */
    void GlotzillaMoleculeList::addMolecule(IAPIMolecule *mole) {
        mMole.push_back(mole);
    }

    /*
     * removeMolecule()
     */
    void GlotzillaMoleculeList::removeMolecule(IAPIMolecule *mole) {

        int index = -1;

        for(int i = 0; i < mMole.size(); i++) {
            if(mMole.at(i) == mole) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            mMole.erase(mMole.begin()+index, mMole.begin()+index+1);
        }
        else {
            printf("WARNING : Attempted to delete a molecule that is not in the molecule list.\n");
        }

    }

    /*
     * clear()
     */
    void GlotzillaMoleculeList::clear() {
        mMole.clear();
    }

}
