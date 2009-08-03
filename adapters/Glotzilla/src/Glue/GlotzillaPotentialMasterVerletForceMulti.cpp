/*
 *  GlotzillaPotentialMasterVerletForceMulti.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletForceMulti.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletForceMulti:: GlotzillaPotentialMasterVerletForceMulti(IAPISimulation *sim) :
                                                                    GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletForceMulti;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletForceMulti::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletForceMulti::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

