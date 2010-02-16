/*
 *  TowheeRandom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

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
        printf("TowheeRandom::nextDouble() is not implemented.\n");
    }

    /*
     * nextInt()
     */
    int TowheeRandom::nextInt(int maxInt) {
        printf("TowheeRandom::nextInt() is not implemented.\n");
    }

    /*
     * nextGaussian()
     */
    double TowheeRandom::nextGaussian() {
        printf("TowheeRandom::nextGaussian() is not implemented.\n");
    }

}
