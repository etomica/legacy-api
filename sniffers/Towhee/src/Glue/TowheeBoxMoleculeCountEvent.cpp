/*
 *  TowheeBoxMoleculeCountEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxMoleculeCountEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxMoleculeCountEvent::TowheeBoxMoleculeCountEvent(IAPISpecies *species, int count, IAPIBox *box) :
                                               TowheeBoxEvent(box) {
        mSpecies = species;
        mCount = count;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeBoxMoleculeCountEvent::getSpecies() {
        return mSpecies;
    }

    /*
     * getCount()
     */
    int TowheeBoxMoleculeCountEvent::getCount() {
        return mCount;
    }

}
