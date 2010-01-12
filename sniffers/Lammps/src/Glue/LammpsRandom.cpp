/*
 *  LammpsRandom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsRandom.h"
#include "LammpsSimulation.h"

namespace lammpssnifferwrappers
{

    LammpsRandom::LammpsRandom(LammpsSimulation *sim, int seed) :
                            LAMMPS_NS::RanMars(sim->getLammpsSim(), seed) {
    }

    /*
     * nextDouble()
     */
    double LammpsRandom::nextDouble() {
        return LAMMPS_NS::RanMars::uniform();
    }

    /*
     * nextInt()
     */
    int LammpsRandom::nextInt(int maxInt) {
        printf("WARNING : LammpsRandom::nextInt() is NOT implemented yet.\n");
    }

    /*
     * nextGaussian()
     */
    double LammpsRandom::nextGaussian() {
        return LAMMPS_NS::RanMars::gaussian();
    }

}
