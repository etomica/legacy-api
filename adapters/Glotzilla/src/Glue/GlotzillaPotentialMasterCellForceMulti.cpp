/*
 *  GlotzillaPotentialMasterCellForceMulti.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterCellForceMulti.h"
#include "GlotzillaPotentialMaster.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterCellForceMulti:: GlotzillaPotentialMasterCellForceMulti(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::CellForceMulti;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

}

