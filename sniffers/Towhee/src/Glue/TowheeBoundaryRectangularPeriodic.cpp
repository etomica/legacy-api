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

    TowheeBoundaryRectangularPeriodic::TowheeBoundaryRectangularPeriodic
                                      (TowheeSpace *space, IAPIVector *size) :
                                              TowheeBoundary(space, size) {
    }

    /*
     * nearestImage()
     */
    void TowheeBoundaryRectangularPeriodic::nearestImage(IAPIVectorMutable *v) {
        printf("TowheeBoundaryRectangularPeriodic::nearestImage(IAPIVectorMutable *) is not implemented.\n");
    }

    /*
     * centralImage()
     */
    IAPIVector *TowheeBoundaryRectangularPeriodic::centralImage(IAPIVector *v) {
        printf("TowheeBoundaryRectangularPeriodic::centralImage(IAPIVectorMutable *) is not implemented.\n");
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

    /*
     * volume()
     */
    double TowheeBoundaryRectangularPeriodic::volume() {
        return mDimensions->getX(0) * mDimensions->getX(1) * mDimensions->getX(2);
    }

}

