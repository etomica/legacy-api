/*
 *  GlotzillaIntegratorLeapFrog.cpp
 *  API Glue
 *
 */


#include "GlotzillaSimulation.h"
#include "GlotzillaIntegratorLeapFrog.h"

namespace glotzwrappers
{

    GlotzillaIntegratorLeapFrog::
        GlotzillaIntegratorLeapFrog(IAPISimulation *sim) : GlotzillaIntegrator(sim) {
        mSimulation = dynamic_cast<GlotzillaSimulation *>(sim)->getGlotzillaSim();
        mIntegrator = new glotzmd::LeapFrogIntegrator;
        mSimulation->SetIntegrationScheme(mIntegrator);
    }

    /*
     * reset()
     */
    void GlotzillaIntegratorLeapFrog::reset() {
        printf("GlotzillaIntegratorLeapFrog::reset() is not implemented.\n");
    }
              
    /*
     * initialize()
     */
    void GlotzillaIntegratorLeapFrog::initialize() {
        printf("GlotzillaIntegratorLeapFrog::initialize() is not implemented.\n");
    }

}
