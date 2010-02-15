/*
 *  LammpsBoundaryCustom.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryCustom.h"

namespace lammpssnifferwrappers
{

    const int LammpsBoundaryCustom::DEFAULT_TYPE = 0;
    const int LammpsBoundaryCustom::PERIODIC = 0;
    const int LammpsBoundaryCustom::FIXED = 1;
    const int LammpsBoundaryCustom::SHRINK = 2;
    const int LammpsBoundaryCustom::SHRINK_MINIMUM = 3;

    LammpsBoundaryCustom::LammpsBoundaryCustom(LammpsSimulation *sim,
                                               int xLower, int xUpper,
                                               int yLower, int yUpper,
                                               int zLower, int zUpper) :
                                                     LammpsBoundary(sim) {
        mXLower = checkTypeBounds(xLower);
        mXUpper = checkTypeBounds(xUpper);
        mYLower = checkTypeBounds(yLower);
        mYUpper = checkTypeBounds(yUpper);
        mZLower = checkTypeBounds(zLower);
        mZUpper = checkTypeBounds(zUpper);

    }

    /*
     * checkTypeBounds()
     */
    int LammpsBoundaryCustom::checkTypeBounds(int type) {
        if(type >= PERIODIC &&
           type <= SHRINK_MINIMUM) {
            return type;
        }
        else {
            return DEFAULT_TYPE;
        }
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundaryCustom::getEdgeVector(int d) {

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
    bool LammpsBoundaryCustom::getPeriodicity(int d) {
        printf("LammpsBoundaryCustom::getPeriodicity(int) is not implemented but should be!\n");
    }

}

