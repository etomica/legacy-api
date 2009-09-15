/*
 *  TowheeAtomList.cpp
 *  API Glue
 *
 */

#include "TowheeAtomList.h"

namespace towheewrappers
{

    TowheeAtomList::TowheeAtomList() {
    }

    /*
     * getAtomCount()
     */
    int TowheeAtomList::getAtomCount() {
        return mAtom.size();
    }

    /*
     * getAtom()
     */
    IAPIAtom *TowheeAtomList::getAtom(int i) {
        return mAtom.at(i);
    }

    /*
     * addAtom()
     */
    void TowheeAtomList::addAtom(IAPIAtom *atom) {
        mAtom.push_back(atom);
    }

    /*
     * removeAtom()
     */
    void TowheeAtomList::removeAtom(IAPIAtom *atom) {

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
    void TowheeAtomList::clear() {
        mAtom.erase(mAtom.begin(), mAtom.end());
    }

}
