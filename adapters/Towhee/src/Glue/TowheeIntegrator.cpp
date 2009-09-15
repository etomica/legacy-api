/*
 *  TowheeIntegrator.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "TowheeIntegrator.h"

extern "C" { void twh_temperature_(int *, double *); }
extern "C" { void main_do_mc_move_(int *); }

namespace towheewrappers
{

    TowheeIntegrator::TowheeIntegrator() {
printf("TowheeIntegrator ctor ...\n"); fflush(stdout);
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
printf("WARNING : TowheeIntegrator::getStepCount() not implemented.\n"); fflush(stdout);
    }

    /*
     * reset()
     */
    void TowheeIntegrator::reset() {
printf("WARNING : TowheeIntegrator::reset() not implemented.\n"); fflush(stdout);
    }

    /*
     * resetStepCount()
     */
    void TowheeIntegrator::resetStepCount() {
printf("WARNING : TowheeIntegrator::resetStepCount() not implemented.\n"); fflush(stdout);
    }

    /*
     * getEventManager()
     */
    IAPIIntegratorEventManager *TowheeIntegrator::getEventManager() {
        return mEventManager;
    }

    /*
     * setTemperature()
     */
    void TowheeIntegrator::setTemperature(double temp) {
        int set = GLB_SET;
        twh_temperature_(&set, &temp);
    }

}
