/*
 *  GlotzillaBoxEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxEvent::GlotzillaBoxEvent(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *GlotzillaBoxEvent::getBox() {
        return mBox;
    }


}
