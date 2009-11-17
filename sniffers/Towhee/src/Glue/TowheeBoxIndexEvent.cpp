/*
 *  TowheeBoxAtomEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeBoxIndexEvent::TowheeBoxIndexEvent(int index, IAPIBox *box) :
                                               TowheeBoxEvent(box) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int TowheeBoxIndexEvent::getIndex() {
        return mIndex;
    }

}
