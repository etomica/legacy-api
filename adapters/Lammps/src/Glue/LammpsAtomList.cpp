/*
 *  LammpsAtomList.cpp
 *  API Glue
 *
 */

#include "LammpsAtomList.h"

namespace lammpswrappers
{

    LammpsAtomList::LammpsAtomList() {
    }

    /*
     * getAtomCount()
     */
    int LammpsAtomList::getAtomCount() {
        return mAtom.size();
    }

    /*
     * getAtom()
     */
    IAPIAtom *LammpsAtomList::getAtom(int i) {
        return mAtom.at(i);
    }

    /*
     * addAtom()
     */
    void LammpsAtomList::addAtom(IAPIAtom *atom) {
        mAtom.push_back(atom);
    }

    /*
     * removeAtom()
     */
    void LammpsAtomList::removeAtom(IAPIAtom *atom) {

        int index = -1;

        for(int i = 0; i < mAtom.size(); i++) {
            if(mAtom.at(i) == atom) {
                index = i;
                break;
            }
        }

        if(index >= 0) {
            mAtom.erase(mAtom.begin()+index, mAtom.begin()+index+1);
        }
        else {
            printf("WARNING : Attempted to delete an atom that is not in the atom list.\n");
        }

    }

    /*
     * clear()
     */
    void LammpsAtomList::clear() {
        mAtom.erase(mAtom.begin(), mAtom.end());
    }

}
