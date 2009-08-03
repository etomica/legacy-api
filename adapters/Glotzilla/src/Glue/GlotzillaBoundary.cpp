/*
 *  GlotzillaBoundary.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "GlotzillaBoundary.h"
#include "GlotzillaBoundaryEventManager.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaBoundary::GlotzillaBoundary(IAPISimulation *sim) {
        mBox = NULL;
        mSpace = dynamic_cast<GlotzillaSimulation *>(sim)->getSpace();
        mVector = dynamic_cast<GlotzillaVector *>(mSpace->makeVector());
        mEventManager = new GlotzillaBoundaryEventManager();
        mCenter = dynamic_cast<GlotzillaVector *>(mSpace->makeVector());
        mCenter->E(0.0);
    }

    /*
     * setBoxSize()
     */
    void GlotzillaBoundary::setBoxSize(IAPIVector *v) {
        mVector->E(v);
        mBoundaryConditions->SetBox(*mVector->getGlotzVector());
    }

    /*
     * getBoxSize()
     */
    IAPIVector *GlotzillaBoundary::getBoxSize() {
        glotzmath::glotz_vec *gVec = &(mBoundaryConditions->GetBox());
        mVector->E(mSpace->makeVector(gVec));

        return mVector;
    }

    /*
     * volume()
     */
    double GlotzillaBoundary::volume() {
        return mBoundaryConditions->GetVolume();
    }

    /*
     * setBox()
     */
    void GlotzillaBoundary::setBox(IAPIBox *box) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *GlotzillaBoundary::getBox() {
        return mBox;
    }

    /*
     * getCenter()
     */
    IAPIVector *GlotzillaBoundary::getCenter() {
        return mCenter;
    }

    /*
     * getEventManager()
     */
    IAPIBoundaryEventManager *GlotzillaBoundary::getEventManager() {
        return mEventManager;
    }

}

