/*
 *  LammpsBoundaryDeformable.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryDeformable.h"

namespace lammpswrappers
{

    LammpsBoundaryDeformable::LammpsBoundaryDeformable(
                                IAPISimulation *sim, int steps,
                                IAPIVector *vecLower, IAPIVector *vecUpper) :
                                                        LammpsBoundary(sim) {
        numSteps = steps;
        mVecLower = mSim->getSpace()->makeVector();
        mVecLower->E(vecLower);
        mVecUpper = mSim->getSpace()->makeVector();
        mVecUpper->E(vecUpper);
        mFixID = NULL;
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundaryDeformable::getEdgeVector(int d) {

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
    bool LammpsBoundaryDeformable::getPeriodicity(int d) {
        return false;
    }

    /*
     * lammpsSetup()
     */
    void LammpsBoundaryDeformable::lammpsSetup() {

        char command[512];

        mFixID = mSim->getFixIDMgr()->getNextID();
        if(mSim->getSpace()->getD() == 2) {
            sprintf(command,
                    "fix %s all deform %d x final %f %f y final %f %f units box",
                    mFixID,
                    numSteps,
                    mVecLower->getX(0), mVecUpper->getX(0),
                    mVecLower->getX(1), mVecUpper->getX(1));
        }
        else {
            sprintf(command,
                    "fix %s all deform %d x final %f %f y final %f %f z final %f %f units box",
                    mFixID,
                    numSteps,
                    mVecLower->getX(0), mVecUpper->getX(0),
                    mVecLower->getX(1), mVecUpper->getX(1),
                    mVecLower->getX(2), mVecUpper->getX(2));
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

    }

}

