/*
 *  GlotzillaBoxAtomIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxAtomIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxAtomIndexEvent::GlotzillaBoxAtomIndexEvent(IAPIAtom *atom, int index, IAPIBox *box) :
                                               GlotzillaBoxAtomEvent(atom, box) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int GlotzillaBoxAtomIndexEvent::getIndex() {
        return mIndex;
    }

}
