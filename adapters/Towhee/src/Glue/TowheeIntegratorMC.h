/*
 *  TowheeIntegratorMC.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_MC_WRAPPER_H
#define TOWHEE_INTEGRATOR_MC_WRAPPER_H

#include <vector>

#include "TowheeIntegrator.h"
#include "TowheeMCMove.h"

namespace towheewrappers
{

    class TowheeIntegratorMC : public TowheeIntegrator {

        public:

            // Non-API methods
            void addMove(TowheeMCMove *move);
            int getMoveCount();
            TowheeMCMove *getMove(int idx);

        private:
            std::vector<TowheeMCMove *>mMoves;

    };
}

#endif
