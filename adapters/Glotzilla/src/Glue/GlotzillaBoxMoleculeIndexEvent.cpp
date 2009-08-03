/*
 *  GlotzillaBoxMoleculeIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxMoleculeIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxMoleculeIndexEvent::GlotzillaBoxMoleculeIndexEvent(IAPIMolecule *mole, int index, IAPIBox *box) :
                                               GlotzillaBoxMoleculeEvent(mole, box) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int GlotzillaBoxMoleculeIndexEvent::getIndex() {
        return mIndex;
    }

}
