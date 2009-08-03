/*
 *  GlotzillaPotentialMasterVerletForceShifted.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletForceShifted.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletForceShifted::
      GlotzillaPotentialMasterVerletForceShifted(IAPISimulation *sim) :
                                             GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletForceShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletForceShifted::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletForceShifted::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

