/*
 *  GlotzillaBoxMoleculeCountEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxMoleculeCountEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxMoleculeCountEvent::GlotzillaBoxMoleculeCountEvent(IAPISpecies *species, int count, IAPIBox *box) :
                                               GlotzillaBoxEvent(box) {
        mSpecies = species;
        mCount = count;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *GlotzillaBoxMoleculeCountEvent::getSpecies() {
        return mSpecies;
    }

    /*
     * getCount()
     */
    int GlotzillaBoxMoleculeCountEvent::getCount() {
        return mCount;
    }

}
