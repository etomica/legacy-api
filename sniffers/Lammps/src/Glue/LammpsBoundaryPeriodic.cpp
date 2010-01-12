/*
 *  LammpsBoundaryPeriodic.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryPeriodic.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryPeriodic::LammpsBoundaryPeriodic(LammpsSimulation *sim) : LammpsBoundary(sim) {
        dimensions = mSim->getSpace()->makeVector();
        dimensionsHalf = mSim->getSpace()->makeVector();
    }

    /*
     * setBoxSize()
     */
    void LammpsBoundaryPeriodic::setBoxSize(IAPIVector *v) {
        LammpsBoundary::setBoxSize(v);
        dimensions->E(v);
        dimensionsHalf->Ea1Tv1(0.5, dimensions);
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundaryPeriodic::getEdgeVector(int d) {

        IAPIVector *bound = getBoxSize();

        IAPIVectorMutable *edge = NULL;

        if(d < mSim->getSpace()->getD()) {
            edge = mSim->getSpace()->makeVector();
            double vals[mSim->getSpace()->getD()];
            for(int i = 0; i < mSim->getSpace()->getD(); i++) {
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
    bool LammpsBoundaryPeriodic::getPeriodicity(int d) {
        return true;
    }

    /*
     * nearestImage()
     */
    void LammpsBoundaryPeriodic::nearestImage(IAPIVectorMutable *v) {
        v->PE(dimensionsHalf);
        v->mod(dimensions);
        v->ME(dimensionsHalf);
    }

    /*
     * centralImage()
     */
    IAPIVector *LammpsBoundaryPeriodic::centralImage(IAPIVector *v) {
printf("WARNING : LammpsBoundary::centralImage() is NOT implemented yet\n");
    }


}

