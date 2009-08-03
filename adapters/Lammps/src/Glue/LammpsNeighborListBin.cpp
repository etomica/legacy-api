/*
 *  LammpsNeighborListBin.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsNeighborListBin.h"

namespace lammpswrappers
{

    LammpsNeighborListBin::LammpsNeighborListBin(IAPISimulation *sim, double cut) :
                                                      LammpsNeighborList(sim, cut) {
        char command[512];
        sprintf(command,
                "neighbor %f bin",
                cutoff);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

}

