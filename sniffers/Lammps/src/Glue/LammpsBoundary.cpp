/*
 *  LammpsBoundary.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "domain.h"

#include "LammpsBoundary.h"

namespace lammpssnifferwrappers
{

    LammpsBoundary::LammpsBoundary(LammpsSimulation *sim) {
        mSim = sim;
        double ***vec = (double ***) malloc(1 * sizeof(double **));
        vec[0] = (double **) malloc (sim->getSpace()->getD() * sizeof(double *));
        if(sim->getSpace()->getD() == 2) {
            vec[0][0] = &mSim->getLammpsSim()->domain->xprd;
            vec[0][1] = &mSim->getLammpsSim()->domain->yprd;
        }
        else {
            vec[0][0] = &mSim->getLammpsSim()->domain->xprd;
            vec[0][1] = &mSim->getLammpsSim()->domain->yprd;
            vec[0][2] = &mSim->getLammpsSim()->domain->zprd;
        }
        mVector = sim->getSpace()->makeVector(vec);
        mBox = NULL;
        mEventMgr = NULL;
        mCenter = sim->getSpace()->makeVector();
        dynamic_cast<IAPIVectorMutable *>(mCenter)->E(0.0);
    }

    /*
     * setBoxSize()
     */
    void LammpsBoundary::setBoxSize(IAPIVector *v) {
        printf("ERROR : LammpsBoundary::setBoxSize(IAPIVector *) is not implemented.\n");
    }

    /*
     * getBoxSize()
     */
    IAPIVector *LammpsBoundary::getBoxSize() {
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
        printf("WARNING : LammpsBoundary::nearestImage() is NOT implemented and should be virtual.\n");
    }

    /*
     * centralImage()
     */
    IAPIVector *LammpsBoundary::centralImage(IAPIVector *v) {
        printf("WARNING : LammpsBoundary::centralImage() is NOT implemented and should be virtual.\n");
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
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundary::getEdgeVector(int d) {

        IAPIVector *bound = getBoxSize();

        if(d < mSim->getSpace()->getD()) {
            mEdge = mSim->getSpace()->makeVector();
            double vals[mSim->getSpace()->getD()];
            for(int i = 0; i < mSim->getSpace()->getD(); i++) {
                vals[i] = 0.0;
            }
            vals[d] = bound->getX(d);
            mEdge->E(vals);
        }
        else
            return NULL;

        return mEdge;
    }

    /*
     *
     */
    IAPIBoundaryEventManager *LammpsBoundary::getEventManager() {
        return mEventMgr;
    }

}

