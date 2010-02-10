/*
 *  LammpsBoundaryPeriodic.cpp
 *  API Glue
 *
 */

#include "library.h"
#include "domain.h"

#include "LammpsBoundaryPeriodic.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryPeriodic::LammpsBoundaryPeriodic(LammpsSimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * setBoxSize()
     */
    void LammpsBoundaryPeriodic::setBoxSize(IAPIVector *v) {
printf(" LammpsBoundaryPeriodic::setBoxSize(IAPIVector) is not impelemented.\n"); fflush(stdout);
//        dimensions->E(v);
//        dimensionsHalf->Ea1Tv1(0.5, dimensions);
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
        IAPIVector *dimensions = getBoxSize();
        IAPIVectorMutable *dimensionsHalf = mSim->getSpace()->makeVector();
        dimensionsHalf->E(dimensions);
        IAPIVectorMutable *half = mSim->getSpace()->makeVector();
        half->E(2);
        dimensionsHalf->DE(half);

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

