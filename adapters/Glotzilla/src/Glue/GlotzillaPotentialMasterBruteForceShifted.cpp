/*
 *  GlotzillaPotentialMasterBruteForceShifted.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterBruteForceShifted.h"
#include "GlotzillaPotentialMaster.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterBruteForceShifted:: GlotzillaPotentialMasterBruteForceShifted(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mBruteForce = new glotzmd::BruteForceShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mBruteForce);
    }

}

