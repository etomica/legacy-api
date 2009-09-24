/*
 *  TowheeIntegratorPseudoBubble.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_PSEUDOBUBBLE_WRAPPER_H
#define TOWHEE_INTEGRATOR_PSEUDOBUBBLE_WRAPPER_H

#include "TowheeIntegratorMC.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorPseudoBubble : public TowheeIntegratorMC {

        public:

            TowheeIntegratorPseudoBubble(double temp);

    };
}

#endif
