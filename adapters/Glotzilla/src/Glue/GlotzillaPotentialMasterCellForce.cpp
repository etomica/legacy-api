/*
 *  GlotzillaPotentialMasterCellForce.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterCellForce.h"
#include "GlotzillaPotentialMaster.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterCellForce:: GlotzillaPotentialMasterCellForce(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::CellForce;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

}

