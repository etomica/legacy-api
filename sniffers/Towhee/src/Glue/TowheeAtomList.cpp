/*
 *  TowheeAtomList.cpp
 *  API Glue
 *
 */

#include "TowheeAtomList.h"

namespace towheesnifferwrappers
{

    /*
     * getAtomCount()
     */
    int TowheeAtomList::getAtomCount() {
        return mAtoms.size();
    }

    /*
     * getAtom()
     */
    IAPIAtom *TowheeAtomList::getAtom(int i) {
        return mAtoms.at(i);
    }

    /*
     * addChildAtom()
     */
    void TowheeAtomList::addChildAtom(IAPIAtom *atom) {
        mAtoms.push_back(atom);
    }


}
