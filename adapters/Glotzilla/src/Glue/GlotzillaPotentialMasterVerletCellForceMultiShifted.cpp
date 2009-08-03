/*
 *  GlotzillaPotentialMasterVerletCellForceMultiShifted.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletCellForceMultiShifted.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletCellForceMultiShifted::
      GlotzillaPotentialMasterVerletCellForceMultiShifted(IAPISimulation *sim) :
                                                 GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletCellForceMultiShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletCellForceMultiShifted::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletCellForceMultiShifted::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

