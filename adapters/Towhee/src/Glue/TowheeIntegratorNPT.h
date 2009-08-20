/*
 *  TowheeIntegratorNPT.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_NPT_WRAPPER_H
#define TOWHEE_INTEGRATOR_NPT_WRAPPER_H

#include "TowheeIntegrator.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorNPT : public TowheeIntegrator {

        public:

            TowheeIntegratorNPT(double temp, double press);

    };
}

#endif
