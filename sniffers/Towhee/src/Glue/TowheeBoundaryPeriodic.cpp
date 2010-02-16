/*
 *  TowheeBoundaryPeriodic.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "TowheeBoundaryPeriodic.h"

namespace towheesnifferwrappers
{

    /*
     * nearestImage()
     */
    void TowheeBoundaryPeriodic::nearestImage(IAPIVectorMutable *v) {
        printf("TowheeBoundaryPeriodic::nearestImage(IAPIVectorMutable *) is not implemented.\n");
    }

    /*
     * centralImage()
     */
    IAPIVector *TowheeBoundaryPeriodic::centralImage(IAPIVector *v) {
        printf("TowheeBoundaryPeriodic::centralImage(IAPIVectorMutable *) is not implemented.\n");
    }

    /*
     * setDimensions()
     */
    void TowheeBoundaryPeriodic::setDimensions(IAPIVector *v) {
        printf("ERROR : TowheeBoundaryPeriodic::setDimensions(IAPIVectorMutable *) is not implemented.\n");
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *TowheeBoundaryPeriodic::getEdgeVector(int d) {
        printf("TowheeBoundaryPeriodic::getEdgeVector(int) is not implemented.\n");
    }

    /*
     * getPeriodicity()
     */
    bool TowheeBoundaryPeriodic::getPeriodicity(int d) {
        printf("TowheeBoundaryPeriodic::getPeriodicity(int) is not implemented.\n");
    }

}

