/*
 *  TowheeBoundaryRectangularPeriodic.cpp
 *  API Glue
 *
 *
 */
#include "stdio.h"

#include "TowheeBoundaryRectangularPeriodic.h"

namespace towheesnifferwrappers
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
//if(mSpace == NULL) {
//printf("mspace is NULL\n"); fflush(stdout);
//}
//else {
//printf("mspace is OK\n"); fflush(stdout);
//}
        if(d < mSpace->getD()) {
            double vals[mSpace->getD()];
            for(int i = 0; i < mSpace->getD(); i++) {
                vals[i] = 0.0;
            }
            vals[d] = mDimensions->getX(d);
            mEdgeVector->E(vals);
        }

//printf(" -- complete\n"); fflush(stdout);
        return mEdgeVector;

    }

    /*
     * getPeriodicity()
     */
    bool TowheeBoundaryRectangularPeriodic::getPeriodicity(int d) {
        return true;
    }

    /*
     * volume()
     */
    double TowheeBoundaryRectangularPeriodic::volume() {
        return mDimensions->getX(0) * mDimensions->getX(1) * mDimensions->getX(2);
    }

}

