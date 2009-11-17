/*
 *  TowheeBoxMoleculeIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxMoleculeIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxMoleculeIndexEvent::TowheeBoxMoleculeIndexEvent(IAPIMolecule *mole, int index, IAPIBox *box) :
                                               TowheeBoxMoleculeEvent(mole, box) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int TowheeBoxMoleculeIndexEvent::getIndex() {
        return mIndex;
    }

}
