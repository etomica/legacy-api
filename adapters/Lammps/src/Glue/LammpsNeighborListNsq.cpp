/*
 *  LammpsNeighborListNsq.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsNeighborListNsq.h"

namespace lammpswrappers
{

    LammpsNeighborListNsq::LammpsNeighborListNsq(IAPISimulation *sim, double cut) :
                                                      LammpsNeighborList(sim, cut) {
        char command[512];
        sprintf(command,
                "neighbor %f nsq",
                cutoff);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

}

