/*
 *  LammpsIntegrator.cpp
 *  API Glue
 *
 */

#include "lammps.h"
#include "library.h"
#include "modify.h"

#include "LammpsIntegrator.h"
#include "LammpsIntegratorEventManager.h"

namespace lammpssnifferwrappers
{

    LammpsIntegrator::LammpsIntegrator(LammpsSimulation *sim) {
        mSimulation = sim;
        mEventManager = (IAPIIntegratorEventManager *)(new LammpsIntegratorEventManager(sim));
        stepCount = 0;
    }
	
    /*
     * doStep()
     */
    void LammpsIntegrator::doStep() {
        char command[512];
        sprintf(command, "run 1");
        lammps_command(mSimulation->getLammpsSim(), command);
        stepCount++;
    }

    /*
     * getStepCount()
     */
    long long LammpsIntegrator::getStepCount() {
        return stepCount;
    }

    /*
     * reset()
     */
    void LammpsIntegrator::reset() {
        printf("WARNING : LammpsIntegrator::reset() is not implemented yet.\n");
    }

    /*
     * resetStepCount()
     */
    void LammpsIntegrator::resetStepCount() {
        stepCount = 0;
    }

    /*
     * getEventManager()
     */
    IAPIIntegratorEventManager *LammpsIntegrator::getEventManager() {
        return mEventManager;
    }

    /*
     * setTimestep()
     */
    void LammpsIntegrator::setTimestep(double ts) {
        char command[512];
        sprintf(command,
                "timestep %f",
                ts);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);
    }

    /*
     * doSteps()
     */
    void LammpsIntegrator::doSteps(int nSteps) {
        char command[512];
        sprintf(command, "run %d",
                nSteps);
        lammps_command(mSimulation->getLammpsSim(), command);
        stepCount += nSteps;
    }

}
