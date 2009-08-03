/*
 *  GlotzillaAtomList.cpp
 *  API Glue
 *
 */

#include <typeinfo>

#include "GlotzillaAtomList.h"

namespace glotzwrappers
{

    GlotzillaAtomList::GlotzillaAtomList() {
    }

    GlotzillaAtomList::~GlotzillaAtomList() {
    }

    /*
     * getAtomCount()
     */
    int GlotzillaAtomList::getAtomCount() {
        return mAtom.size();
    }

    /*
     * getAtom()
     */
    IAPIAtom *GlotzillaAtomList::getAtom(int i) {
        return mAtom.at(i);
    }

    /*
     * addAtom()
     */
    void GlotzillaAtomList::addAtom(IAPIAtom *atom) {
        mAtom.push_back(atom);
    }

    /*
     * removeAtom()
     */
    void GlotzillaAtomList::removeAtom(IAPIAtom *atom) {

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
    void GlotzillaAtomList::clear() {
        mAtom.clear();
    }

}
