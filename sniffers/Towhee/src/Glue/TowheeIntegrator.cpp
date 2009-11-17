/*
 *  TowheeIntegrator.cpp
 *  API Glue
 *
 */
#include "stdio.h"

#include "preproc.h"

#include "TowheeIntegrator.h"

extern "C" { void twh_ensemble_(int *, int *); }
extern "C" { void main_do_mc_move_(int *); }

namespace towheesnifferwrappers
{

    TowheeIntegrator::TowheeIntegrator() {
        mEventManager = new TowheeIntegratorEventManager();
    }

    /*
     * doStep()
     */
    void TowheeIntegrator::doStep() {
        int failure = 0;
//printf("Calling doStep!\n"); fflush(stdout);
        mEventManager->stepStartedNotify();
        main_do_mc_move_(&failure);
        mEventManager->stepCompletedNotify();
    }

    /*
     * getStepCount()
     */
    long long TowheeIntegrator::getStepCount() {
    }

    /*
     * reset()
     */
    void TowheeIntegrator::reset() {
    }

    /*
     * resetStepCount()
     */
    void TowheeIntegrator::resetStepCount() {
    }

    /*
     * getEventManager()
     */
    IAPIIntegratorEventManager *TowheeIntegrator::getEventManager() {
        return mEventManager;
    }

    /*
     * getEnsemble()
     */
    int TowheeIntegrator::getEnsemble() {
        int set = GLB_SET;
        int ensemble;
        twh_ensemble_(&set, &ensemble);

        return ensemble;
    }

}
