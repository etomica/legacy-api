/*
 *  GlotzillaPotentialMasterVerletCellForceMulti.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletCellForceMulti.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletCellForceMulti:: 
        GlotzillaPotentialMasterVerletCellForceMulti(IAPISimulation *sim) :
                                                GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletCellForceMulti;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletCellForceMulti::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletCellForceMulti::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

