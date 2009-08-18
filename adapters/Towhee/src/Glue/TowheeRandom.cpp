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
extern "C" { void twh_random_allow_restart_(int *, int *); }
extern "C" { void twh_init_random_single_(); }

namespace towheewrappers
{

    TowheeRandom::TowheeRandom(bool allowRestart) {
        int set = GLB_SET;
        int allow = 0;
        if(allowRestart) allow = 1;
        twh_random_allow_restart_(&set, &allow);
        if(!allowRestart) twh_init_random_single_();
    }

    TowheeRandom::TowheeRandom(bool allowRestart, long seed) {
        int set = GLB_SET;
        int allow = 0;
        if(allowRestart) allow = 1;
        twh_random_allow_restart_(&set, &allow);
        twh_randomseed_(&set, &seed);
        if(!allowRestart) twh_init_random_single_();
    }

    TowheeRandom::TowheeRandom(bool allowRestart, long seed, int luxLevel) {
        int set = GLB_SET;
        int allow = 0;
        if(allowRestart) allow = 1;
        twh_random_allow_restart_(&set, &allow);
        twh_randomseed_(&set, &seed);
        if(luxLevel >= 0 && luxLevel <= 4) {
            twh_random_luxlevel_(&set, &luxLevel);
        }
        if(!allowRestart) twh_init_random_single_();
    }

    /*
     * nextDouble()
     */
    double TowheeRandom::nextDouble() {
        printf("WARNING : TowheeRandom::nextDouble() is NOT implemented yet.\n");
    }

    /*
     * nextInt()
     */
    int TowheeRandom::nextInt(int maxInt) {
        printf("WARNING : TowheeRandom::nextInt() is NOT implemented yet.\n");
    }

    /*
     * nextGaussian()
     */
    double TowheeRandom::nextGaussian() {
        printf("WARNING : TowheeRandom::nextGaussian() is NOT implemented yet.\n");
    }

}
