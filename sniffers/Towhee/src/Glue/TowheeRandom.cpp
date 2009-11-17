/*
 *  TowheeRandom.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeRandom.h"

extern "C" { void twh_randomseed_(int *, long *); }
extern "C" { void twh_random_luxlevel_(int *, int *); }

namespace towheesnifferwrappers
{

    TowheeRandom::TowheeRandom(long seed) {
        int set = GLB_SET;
        twh_randomseed_(&set, &seed);
    }

    TowheeRandom::TowheeRandom(long seed, int luxLevel) {
        int set = GLB_SET;
        twh_randomseed_(&set, &seed);
        if(luxLevel >= 0 && luxLevel <= 4) {
            twh_random_luxlevel_(&set, &luxLevel);
        }
    }

    /*
     * nextDouble()
     */
    double TowheeRandom::nextDouble() {
    }

    /*
     * nextInt()
     */
    int TowheeRandom::nextInt(int maxInt) {
    }

    /*
     * nextGaussian()
     */
    double TowheeRandom::nextGaussian() {
    }

}
