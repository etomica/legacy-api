/*
 *  TowheeIntegratorUVT.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeIntegratorUVT.h"

extern "C" { void twh_tmmc_flag_(int *, int *); }
extern "C" { void twh_ensemble_(int *, int *); }

namespace towheewrappers
{

    TowheeIntegratorUVT::TowheeIntegratorUVT(double temp, bool tmmc) {
        int set = GLB_SET;

        // Set ensemble
        int ensemble = ENS_UVT;
        twh_ensemble_(&set, &ensemble);

        // Set temperature
        setTemperature(temp);

        // Set transition matrix Monte Carlo flag
        int tmmcFlag = 0;
        if(tmmc) tmmcFlag = 1;
        twh_tmmc_flag_(&set, &tmmcFlag);

    }

}
