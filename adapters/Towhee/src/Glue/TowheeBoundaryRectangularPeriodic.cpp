/*
 *  TowheeBoundaryRectangularPeriodic.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "TowheeBoundaryRectangularPeriodic.h"

namespace towheewrappers
{

    TowheeBoundaryRectangularPeriodic::TowheeBoundaryRectangularPeriodic(TowheeSpace *space) :
                                              TowheeBoundary(space) {
    }

    /*
     * nearestImage()
     */
    void TowheeBoundaryRectangularPeriodic::nearestImage(IAPIVectorMutable *v) {
    }

    /*
     * centralImage()
     */
    IAPIVector *TowheeBoundaryRectangularPeriodic::centralImage(IAPIVector *v) {
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *TowheeBoundaryRectangularPeriodic::getEdgeVector(int d) {
        if(d < mSpace->getD()) {
            double vals[mSpace->getD()];
            for(int i = 0; i < mSpace->getD(); i++) {
                vals[i] = 0.0;
            }
            vals[d] = mDimensions->getX(d);
            mEdgeVector->E(vals);
        }

        return mEdgeVector;
    }

    /*
     * getPeriodicity()
     */
    bool TowheeBoundaryRectangularPeriodic::getPeriodicity(int d) {
        return true;
    }

}

