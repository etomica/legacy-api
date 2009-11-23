/*
 *  TowheeIntegratorNVT.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeIntegratorNVT.h"


extern "C" { void twh_ensemble_(int *, int *); }

namespace towheewrappers
{

    TowheeIntegratorNVT::TowheeIntegratorNVT(double temp) {
        int set = GLB_SET;
        int ensemble = ENS_NVT;
        twh_ensemble_(&set, &ensemble);
        setTemperature(temp);
    }

}
