/*
 *  GlotzillaBoxAtomEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxIndexEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxIndexEvent::GlotzillaBoxIndexEvent(int index, IAPIBox *box) :
                                               GlotzillaBoxEvent(box) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int GlotzillaBoxIndexEvent::getIndex() {
        return mIndex;
    }

}
