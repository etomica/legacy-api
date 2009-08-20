/*
 *  TowheeIntegratorNVT.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_NVT_WRAPPER_H
#define TOWHEE_INTEGRATOR_NVT_WRAPPER_H

#include "TowheeIntegrator.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorNVT : public TowheeIntegrator {

        public:

            TowheeIntegratorNVT(double temp);

    };
}

#endif
