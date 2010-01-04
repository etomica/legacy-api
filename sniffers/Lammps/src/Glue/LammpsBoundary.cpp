/*
 *  LammpsBoundary.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "domain.h"

#include "LammpsBoundary.h"

//#include "LammpsBoundaryPeriodic.h"
//#include "LammpsBoundaryFixed.h"
//#include "LammpsBoundaryShrink.h"
//#include "LammpsBoundaryShrinkMin.h"
//#include "LammpsBoundaryCustom.h"

namespace lammpssnifferwrappers
{

    LammpsBoundary::LammpsBoundary(LammpsSimulation *sim) {
        mSim = sim;
        mSpace = sim->getSpace();
        double **vec = (double **) malloc (mSpace->getD() * sizeof(double *));
        if(mSpace->getD() == 2) {
            vec[0] = &mSim->getLammpsSim()->domain->xprd;
            vec[1] = &mSim->getLammpsSim()->domain->yprd;
        }
        else {
            vec[0] = &mSim->getLammpsSim()->domain->xprd;
            vec[1] = &mSim->getLammpsSim()->domain->yprd;
            vec[2] = &mSim->getLammpsSim()->domain->zprd;
        }
        mVector = mSpace->makeVector(vec);
//        mCenter = mSpace->makeVector();
        mBox = NULL;
        mEventMgr = NULL;
    }

    /*
     * setBoxSize()
     */
    void LammpsBoundary::setBoxSize(IAPIVector *v) {
        printf("LammpsBoundary::setBoxSize should not be called.\n");
    }

    /*
     * getBoxSize()
     */
    IAPIVector *LammpsBoundary::getBoxSize() {
        if(mSpace->getD() == 2) {
            double dim[] = {mSim->getLammpsSim()->domain->xprd,
                            mSim->getLammpsSim()->domain->yprd};
            mVector->E(dim);
        }
        else if(mSim->getSpace()->getD() == 3) {
            double dim[] = {mSim->getLammpsSim()->domain->xprd,
                            mSim->getLammpsSim()->domain->yprd,
                            mSim->getLammpsSim()->domain->zprd};
            mVector->E(dim);
        }
        return mVector;
    }

    /*
     * volume()
     */
    double LammpsBoundary::volume() {
        double volume = 0.0;
        if (mSim->getLammpsSim()->domain->dimension == 3) {
            volume = mSim->getLammpsSim()->domain->xprd *
                     mSim->getLammpsSim()->domain->yprd *
                     mSim->getLammpsSim()->domain->zprd;
        }
        else {
            volume = mSim->getLammpsSim()->domain->xprd *
                     mSim->getLammpsSim()->domain->yprd;
        }

        return volume;
    }

    /*
     * nearestImage()
     */
    void LammpsBoundary::nearestImage(IAPIVectorMutable *v) {
printf("WARNING : LammpsBoundary::nearestImage() is NOT implemented yet\n");
    }

    /*
     * centralImage()
     */
    IAPIVector *LammpsBoundary::centralImage(IAPIVector *v) {
printf("WARNING : LammpsBoundary::centralImage() is NOT implemented yet\n");
    }

    /*
     * getCenter()
     */
    IAPIVector *LammpsBoundary::getCenter() {
//        return mCenter;
printf("WARNING : LammpsBoundary::getCenter(0 is NOT implemented yet.  Need a 'local' vector class.\n");
    }

    /*
     * setBox()
     */
    void LammpsBoundary::setBox(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *LammpsBoundary::getBox() {
        return mBox;
    }

    /*
     *
     */
    IAPIBoundaryEventManager *LammpsBoundary::getEventManager() {
        return mEventMgr;
    }

}

