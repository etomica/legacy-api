/*
 *  LammpsRandom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsRandom.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    LammpsRandom::LammpsRandom(IAPISimulation *sim, int seed) :
                            LAMMPS_NS::RanMars(dynamic_cast<LammpsSimulation *>(sim)->getLammpsSim(), seed) {
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
