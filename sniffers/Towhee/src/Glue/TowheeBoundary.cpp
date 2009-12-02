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

    TowheeBoundary::TowheeBoundary(TowheeSpace *space) {
        mSpace = space;
        mDimensions = space->makeVector();
        mCenter = space->makeVector();
        mEdgeVector = space->makeVector();
    }

    /*
     * setBoxSize()
     */
    void TowheeBoundary::setBoxSize(IAPIVector *v) {
        for(int i = 0; i < v->getD(); i++) {
            mDimensions->setX(i, v->getX(i));
            mCenter->setX(i, v->getX(i) / 2.0);
        }
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
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeBoundary::getBox() {
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

