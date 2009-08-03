/*
 *  LammpsNeighborList.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsNeighborList.h"

namespace lammpswrappers
{

    LammpsNeighborList::LammpsNeighborList(IAPISimulation *sim, double cut) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        cutoff = cut;
    }

    /*
     * setDelay()
     */
    void LammpsNeighborList::setDelay(int val) {
        char command[256];
        sprintf(command,
                "neigh_modify delay %d",
                val);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * setEvery()
     */
    void LammpsNeighborList::setEvery(int val) {
        char command[256];
        sprintf(command,
                "neigh_modify every %d",
                val);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * setCheck()
     */
    void LammpsNeighborList::setCheck(bool val) {
        char command[256];
        if(val) {
            sprintf(command,
                    "neigh_modify check yes");
        }
        else {
            sprintf(command,
                    "neigh_modify check no");
        }
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * setPage()
     */
    void LammpsNeighborList::setPage(int val) {
        char command[256];
        sprintf(command,
                "neigh_modify page %d",
                val);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * setOne()
     */
    void LammpsNeighborList::setOne(int val) {
        char command[256];
        sprintf(command,
                "neigh_modify one %d",
                val);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * setBinSize()
     */
    void LammpsNeighborList::setBinSize(int val) {
        char command[256];
        sprintf(command,
                "neigh_modify binsize %d",
                val);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

}

