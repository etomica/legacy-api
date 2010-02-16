/*
 *  TowheeBoxEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxEvent::TowheeBoxEvent(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeBoxEvent::getBox() {
        return mBox;
    }


}
