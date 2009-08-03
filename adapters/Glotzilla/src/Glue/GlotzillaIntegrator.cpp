/*
 *  GlotzillaIntegrator.cpp
 *  API Glue
 *
 */

#include "GlotzillaIntegrator.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaIntegrator::GlotzillaIntegrator(IAPISimulation *sim) {
        mSimulation = dynamic_cast<GlotzillaSimulation *>(sim)->getGlotzillaSim();
        mEventManager = new GlotzillaIntegratorEventManager(sim);
    }
	
    /*
     * doStep()
     */
    void GlotzillaIntegrator::doStep() {
        mSimulation->StepForward(1);
    }

    /*
     * getStepCount()
     */
    long long GlotzillaIntegrator::getStepCount() {
        return mSimulation->GetTimesteps();
    }

    /*
     * resetStepCount()
     */
    void GlotzillaIntegrator::resetStepCount() {
        mSimulation->gTimesteps = 0;
    }

    /*
     * getEventManager()
     */
    IAPIIntegratorEventManager *GlotzillaIntegrator::getEventManager() {
        return mEventManager;
    }

    /*
     * setTimestep()
     */
    void GlotzillaIntegrator::setTimestep(double fs) {
        printf("GlotzillaIntegrator::setTimestep() NOT implemented yet.\n"); fflush(stdout);
        // Need to fire an event to glotzilla so the event manager gets it and changes
        // the timestep.  Cannot call SetTimestep() directly on the integrator.
    }

}
