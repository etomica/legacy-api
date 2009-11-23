/*
 *  TowheeIntegratorNPT.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeIntegratorNPT.h"

extern "C" { void twh_express_(int *, double *); }
extern "C" { void twh_ensemble_(int *, int *); }

namespace towheewrappers
{

    TowheeIntegratorNPT::TowheeIntegratorNPT(double temp, double press) {
        int set = GLB_SET;

        // Set ensemble
        int ensemble = ENS_NPT;
        twh_ensemble_(&set, &ensemble);

        // Set temperature
        setTemperature(temp);

        // Set pressure
        // Convert from kPa (given) to simulation units
        // CON_KPATOSIM on towhee simulation engine side (format not
        // acceptable on C side)
        double CONVERSION = 7.2429E-5;
        double pressure = press * CONVERSION;
        twh_express_(&set, &pressure);
    }

}
