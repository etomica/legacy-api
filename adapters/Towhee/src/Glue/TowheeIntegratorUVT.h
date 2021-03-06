/*
 *  TowheeIntegratorUVT.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_UVT_WRAPPER_H
#define TOWHEE_INTEGRATOR_UVT_WRAPPER_H

#include "TowheeIntegratorMC.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorUVT : public TowheeIntegratorMC {

        public:

            TowheeIntegratorUVT(double temp, bool tmmc);

    };
}

#endif
