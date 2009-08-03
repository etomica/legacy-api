/*
 *  GlotzillaIntegratorEuler.cpp
 *  API Glue
 *
 */


#include "GlotzillaSimulation.h"
#include "GlotzillaIntegratorEuler.h"

namespace glotzwrappers
{

    GlotzillaIntegratorEuler::
        GlotzillaIntegratorEuler(IAPISimulation *sim) : GlotzillaIntegrator(sim) {
        mSimulation = dynamic_cast<GlotzillaSimulation *>(sim)->getGlotzillaSim();
        mIntegrator = new glotzmd::EulerIntegrator;
        mSimulation->SetIntegrationScheme(mIntegrator);
    }

    /*
     * reset()
     */
    void GlotzillaIntegratorEuler::reset() {
        printf("GlotzillaIntegratorEuler::reset() is not implemented.\n");
    }

    /*
     * initialize()
     */
    void GlotzillaIntegratorEuler::initialize() {
        printf("GlotzillaIntegratorEuler::initialize() is not implemented.\n");
    }

}
