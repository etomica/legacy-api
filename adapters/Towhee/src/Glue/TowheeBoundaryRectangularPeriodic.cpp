/*
 *  TowheeBoundaryRectangularPeriodic.cpp
 *  API Glue
 *
 *
 */

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
    }

    /*
     * getPeriodicity()
     */
    bool TowheeBoundaryRectangularPeriodic::getPeriodicity(int d) {
        return true;
    }

}

