/*
 *  TowheeIntegratorNVT.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_NVT_WRAPPER_H
#define TOWHEE_INTEGRATOR_NVT_WRAPPER_H

#include "TowheeIntegratorMC.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorNVT : public TowheeIntegratorMC {

        public:

            TowheeIntegratorNVT(double temp);

    };
}

#endif
