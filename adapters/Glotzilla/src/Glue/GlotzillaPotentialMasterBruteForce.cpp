/*
 *  GlotzillaPotentialMasterBruteForce.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterBruteForce.h"
#include "GlotzillaPotentialMaster.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterBruteForce:: GlotzillaPotentialMasterBruteForce(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mBruteForce = new glotzmd::BruteForce;
        mSim->getGlotzillaSim()->SetForceRoutine(mBruteForce);
    }

}

