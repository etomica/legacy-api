/*
 *  LammpsNeighborListMulti.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsNeighborListMulti.h"

namespace lammpswrappers
{

    LammpsNeighborListMulti::LammpsNeighborListMulti(IAPISimulation *sim, double cut) :
                                                      LammpsNeighborList(sim, cut) {
        char command[512];
        sprintf(command,
                "neighbor %f multi",
                cutoff);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

}

