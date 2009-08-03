/*
 *  GlotzillaBoundaryPeriodic.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "GlotzillaBoundaryPeriodic.h"

namespace glotzwrappers
{

    GlotzillaBoundaryPeriodic::GlotzillaBoundaryPeriodic(IAPISimulation *sim) : GlotzillaBoundary(sim) {
        mBoundaryConditions = new glotzsimapi::PeriodicBoundary();
        dimensions = mSpace->makeVector();
        dimensionsHalf = mSpace->makeVector();
    }

    GlotzillaBoundaryPeriodic::GlotzillaBoundaryPeriodic(IAPISimulation *sim,
                  glotzsimapi::PeriodicBoundary* boundaryConditions) : GlotzillaBoundary(sim) {

        mBoundaryConditions = boundaryConditions;
        glotzmath::glotz_vec *vec = &(mBoundaryConditions->GetBox());
        dimensions = mSpace->makeVector(vec);
        dimensionsHalf = mSpace->makeVector();
        dimensionsHalf->Ea1Tv1(0.5, dimensions);
    }

    /*
     * nearestImage()
     */
    void GlotzillaBoundaryPeriodic::nearestImage(IAPIVectorMutable *v) {
        v->PE(dimensionsHalf);
        v->mod(dimensions);
        v->ME(dimensionsHalf);
    }

    /*
     * centralImage()
     */
    IAPIVector *GlotzillaBoundaryPeriodic::centralImage(IAPIVector *v) {
printf("WARNING : GlotzillaBoundaryPeriodic::centralImage() is NOT implemented yet\n");
// tempImage = some blank vector (originally)
//        tempImage.E(r);
//        nearestImage(tempImage);
//        tempImage.ME(r);
//        return tempImage;
    }

    /*
     * setBoxSize()
     */
    void GlotzillaBoundaryPeriodic::setBoxSize(IAPIVector *v) {
        GlotzillaBoundary::setBoxSize(v);
        dimensions->E(v);
        dimensionsHalf->Ea1Tv1(0.5, dimensions);
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *GlotzillaBoundaryPeriodic::getEdgeVector(int d) {
        glotzmath::glotz_vec *gVec = &(mBoundaryConditions->GetBox());
        IAPIVector *bound = mSpace->makeVector(gVec);

        IAPIVectorMutable *edge = NULL;

        if(d < mSpace->getD()) {
            edge = mSpace->makeVector();
            double vals[mSpace->getD()];
            for(int i = 0; i < mSpace->getD(); i++) {
                vals[i] = 0.0;
            } 
            vals[d] = bound->getX(d);
            edge->E(vals);
        }

        return edge;
    }

    /*
     * getPeriodicity()
     */
    bool GlotzillaBoundaryPeriodic::getPeriodicity(int d) {
        return true;
    }

}

