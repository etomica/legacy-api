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
        mEventManager->stepStartedNotify();
        main_do_mc_move_(&failure);
        mEventManager->stepCompletedNotify();
    }

    /*
     * getStepCount()
     */
    long long TowheeIntegrator::getStepCount() {
        printf("TowheeIntegrator::getStepCount() is not implemented.\n");
    }

    /*
     * reset()
     */
    void TowheeIntegrator::reset() {
        printf("TowheeIntegrator::reset() is not implemented.\n");
    }

    /*
     * resetStepCount()
     */
    void TowheeIntegrator::resetStepCount() {
        printf("TowheeIntegrator::resetStepCount() is not implemented.\n");
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
