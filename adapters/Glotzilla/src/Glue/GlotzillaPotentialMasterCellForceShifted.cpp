/*
 *  GlotzillaPotentialMasterCellForceShifted..cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterCellForceShifted.h"
#include "GlotzillaPotentialMaster.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterCellForceShifted::
       GlotzillaPotentialMasterCellForceShifted(IAPISimulation *sim) :
                                                GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::CellForceShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

}

