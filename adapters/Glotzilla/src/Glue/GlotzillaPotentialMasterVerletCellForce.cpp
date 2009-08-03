/*
 *  GlotzillaPotentialMasterVerletCellForce.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletCellForce.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterVerletCellForce::GlotzillaPotentialMasterVerletCellForce(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletCellForce;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletCellForce::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletCellForce::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

