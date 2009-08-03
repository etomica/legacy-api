/*
 *  LammpsBoundary.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "domain.h"

#include "LammpsBoundary.h"

#include "LammpsBoundaryPeriodic.h"
#include "LammpsBoundaryFixed.h"
#include "LammpsBoundaryShrink.h"
#include "LammpsBoundaryShrinkMin.h"
#include "LammpsBoundaryCustom.h"

namespace lammpswrappers
{

    LammpsBoundary::LammpsBoundary(IAPISimulation *sim) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        mVector = mSim->getSpace()->makeVector();
        mCenter = mSim->getSpace()->makeVector();
        mBox = NULL;
        mEventMgr = NULL;
    }

    /*
     * setBoxSize()
     */
    void LammpsBoundary::setBoxSize(IAPIVector *v) {
        if(mSim->getState() == LammpsSimulation::UNINITIALIZED) {
            mVector->E(v);
        }
        else {
            printf("ERROR : LammpsBoundary::setBoxSize cannot be called after simulation initialized.\n");
        }
    }

    /*
     * getBoxSize()
     */
    IAPIVector *LammpsBoundary::getBoxSize() {
        if(mSim->getState() == LammpsSimulation::INITIALIZED) {
            if(mSim->getSpace()->getD() == 2) {
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
        return mCenter;
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

