/*
 *  LammpsIntegratorRespa.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsIntegratorRespa.h"

namespace lammpswrappers
{

    LammpsIntegratorRespa::LammpsIntegratorRespa(IAPISimulation *sim, int nLvl,
                                                 int lvl[]) : LammpsIntegrator(sim) {
        numRespaLevels = nLvl;
        if(respaLoopFactor != NULL) {
            free(respaLoopFactor);
        }
        respaLoopFactor = (int *) malloc ((numRespaLevels-1) * sizeof(int));
        for(int i = 0; i < numRespaLevels-1; i++) {
            respaLoopFactor[i] = lvl[i];
        }

    }

    /*
     * lammpsSetup()
     */
    void LammpsIntegratorRespa::lammpsSetup() {

        char command[512];

        sprintf(command,
                "run_style respa %d ",
                numRespaLevels);
        for(int i = 0; i < numRespaLevels-1; i++) {
            sprintf(command,
                    "%s %d ",
                    command,
                    respaLoopFactor[i]);
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);

        LammpsIntegrator::lammpsSetup();

    }

}
