/*
 *  LammpsBoundaryShrinkMin.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryShrinkMin.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    LammpsBoundaryShrinkMin::LammpsBoundaryShrinkMin(IAPISimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundaryShrinkMin::getEdgeVector(int d) {

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
    bool LammpsBoundaryShrinkMin::getPeriodicity(int d) {
        return false;
    }

    /*
     * lammpsSetup()
     */
    void LammpsBoundaryShrinkMin::lammpsSetup() {

        char command[512];

printf("lammps_command : boundary m m m\n"); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), "boundary m m m");

    }

}

