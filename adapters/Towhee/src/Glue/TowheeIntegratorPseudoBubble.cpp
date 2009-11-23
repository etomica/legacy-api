/*
 *  TowheeIntegratorPseudoBubble.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeIntegratorPseudoBubble.h"

extern "C" { void twh_ensemble_(int *, int *); }

namespace towheewrappers
{

    TowheeIntegratorPseudoBubble::TowheeIntegratorPseudoBubble(double temp) {
        int set = GLB_SET;
        int ensemble = ENS_BUBBLE;
        twh_ensemble_(&set, &ensemble);
        setTemperature(temp);
    }

}
