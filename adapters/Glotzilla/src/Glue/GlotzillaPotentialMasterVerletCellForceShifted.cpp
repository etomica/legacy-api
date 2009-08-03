/*
 *  GlotzillaPotentialMasterVerletCellForceShifted.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletCellForceShifted.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletCellForceShifted:: GlotzillaPotentialMasterVerletCellForceShifted(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletCellForceShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletCellForceShifted::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletCellForceShifted::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

