/*
 *  GlotzillaPotentialMasterVerletForceMultiShifted.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialMasterVerletForceMultiShifted.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaPotentialMasterVerletForceMultiShifted::
      GlotzillaPotentialMasterVerletForceMultiShifted(IAPISimulation *sim) :
                                              GlotzillaPotentialMaster(sim) {
        mForce = new glotzmd::VerletForceMultiShifted;
        mSim->getGlotzillaSim()->SetForceRoutine(mForce);
    }

    /*
     * setListUpdateFrequency
     */
    void GlotzillaPotentialMasterVerletForceMultiShifted::setListUpdateFrequency(int freq) {
        mForce->SetListUpdateFrequency(freq);
    }

    /*
     * setSkinThickness
     */
    void GlotzillaPotentialMasterVerletForceMultiShifted::setSkinThickness(double thick) {
        mForce->SetSkinThickness(thick);
    }

}

