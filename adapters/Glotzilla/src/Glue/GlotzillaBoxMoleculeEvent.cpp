/*
 *  GlotzillaBoxMoleculeEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxMoleculeEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxMoleculeEvent::GlotzillaBoxMoleculeEvent(IAPIMolecule *mole, IAPIBox *box) :
                                               GlotzillaBoxEvent(box) {
        mMolecule = mole;
    }

    /*
     * getMolecule()
     */
    IAPIMolecule *GlotzillaBoxMoleculeEvent::getMolecule() {
        return mMolecule;
    }

}
