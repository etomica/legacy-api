/*
 *  LammpsBoundaryCustom.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryCustom.h"

namespace lammpssnifferwrappers
{

    const char *const LammpsBoundaryCustom::bondTypes = "pfsm";
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

        mBoundaryArg = (char *) malloc (9 * sizeof(char));

        sprintf(mBoundaryArg,
                "%c%c %c%c %c%c",
                bondTypes[mXLower],
                bondTypes[mXUpper],
                bondTypes[mYLower],
                bondTypes[mYUpper],
                bondTypes[mZLower],
                bondTypes[mZUpper]);

    }

    /*
     * getBoundaryArgument()
     */
    char *LammpsBoundaryCustom::getBoundaryArgument() {
        return mBoundaryArg;
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
    }

    /*
     * lammpsSetup()
     */
    void LammpsBoundaryCustom::lammpsSetup() {

        char command[512];

        sprintf(command,
                "boundary %s",
                dynamic_cast<LammpsBoundaryCustom *>(this)->getBoundaryArgument());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

    }

}

