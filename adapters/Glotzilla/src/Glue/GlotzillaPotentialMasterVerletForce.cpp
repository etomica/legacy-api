/*
 *  GlotzillaPotentialMasterVerletForce.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletForce.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{


    GlotzillaPotentialMasterVerletForce::
      GlotzillaPotentialMasterVerletForce(IAPISimulation *sim) :
                                           GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletForce;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletForce::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletForce::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

