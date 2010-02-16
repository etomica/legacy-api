/*
 *  TowheeBoundary.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "TowheeBoundary.h"

namespace towheesnifferwrappers
{

    TowheeBoundary::TowheeBoundary(TowheeSpace *space, IAPIVector *size) {
        mSpace = space;
        mDimensions = space->makeVector();
        mCenter = space->makeVector();
        mEdgeVector = space->makeVector();
        for(int i = 0; i < size->getD(); i++) {
            mDimensions->setX(i, size->getX(i));
            mCenter->setX(i, size->getX(i) / 2.0);
        }
    }

    /*
     * setBoxSize()
     */
    void TowheeBoundary::setBoxSize(IAPIVector *v) {
        printf("TowheeBoundary::setBoxSize(IAPIVector *) is not implemented.\n");
    }

    /*
     * getBoxSize()
     */
    IAPIVector *TowheeBoundary::getBoxSize() {
        return mDimensions;
    }

    /*
     * setBox()
     */
    void TowheeBoundary::setBox(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeBoundary::getBox() {
        return mBox;
    }

    /*
     * getCenter()
     */
    IAPIVector *TowheeBoundary::getCenter() {
        return mCenter;
    }

    /*
     * getEventManager()
     */
    IAPIBoundaryEventManager *TowheeBoundary::getEventManager() {
    }

}

