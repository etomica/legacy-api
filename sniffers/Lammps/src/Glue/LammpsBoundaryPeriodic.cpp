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
        printf("ERROR : LammpsBoundaryPeriodic::setBoxSize(IAPIVector) is not impelemented.\n"); fflush(stdout);
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

        delete dimensionsHalf;
        delete half;
    }

    /*
     * centralImage()
     */
    IAPIVector *LammpsBoundaryPeriodic::centralImage(IAPIVector *v) {
printf("WARNING : LammpsBoundary::centralImage() is NOT implemented yet\n");
    }


}

