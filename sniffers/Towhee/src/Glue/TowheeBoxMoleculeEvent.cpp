/*
 *  TowheeBoxMoleculeEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxMoleculeEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxMoleculeEvent::TowheeBoxMoleculeEvent(IAPIMolecule *mole, IAPIBox *box) :
                                               TowheeBoxEvent(box) {
        mMolecule = mole;
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *TowheeBoxMoleculeEvent::getMolecule() {
        return mMolecule;
    }

}
