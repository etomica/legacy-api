/*
 *  GlotzillaIntegratorVelocityVerlet.cpp
 *  API Glue
 *
 */


#include "GlotzillaSimulation.h"
#include "GlotzillaIntegratorVelocityVerlet.h"

namespace glotzwrappers
{

    GlotzillaIntegratorVelocityVerlet::
        GlotzillaIntegratorVelocityVerlet(IAPISimulation *sim) : GlotzillaIntegrator(sim) {
        mSimulation = dynamic_cast<GlotzillaSimulation *>(sim)->getGlotzillaSim();
        mIntegrator = new glotzmd::VelocityVerletIntegrator;
        mSimulation->SetIntegrationScheme(mIntegrator);
    }

    /*
     * reset()
     */
    void GlotzillaIntegratorVelocityVerlet::reset() {
        printf("GlotzillaIntegratorVelocityVerlet::reset() is not implemented.\n");
        fflush(stdout);
    }
              
    /*
     * initialize()
     */
    void GlotzillaIntegratorVelocityVerlet::initialize() {
        printf("GlotzillaIntegratorVelocityVerlet::initialize() is not implemented.\n");
        fflush(stdout);
    }

}
