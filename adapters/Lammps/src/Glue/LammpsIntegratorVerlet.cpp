/*
 *  LammpsIntegratorVerlet.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsIntegratorVerlet.h"

namespace lammpswrappers
{

    LammpsIntegratorVerlet::LammpsIntegratorVerlet(IAPISimulation *sim)
                                                     : LammpsIntegrator(sim) {
    }

    /*
     * lammpsSetup()
     */
    void LammpsIntegratorVerlet::lammpsSetup() {

        char command[512];

        sprintf(command,
                "run_style verlet ");

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);

        LammpsIntegrator::lammpsSetup();

    }

}
