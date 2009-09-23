/*
 *  TowheeMCMove.h
 *  API Glue
 *
 */

#ifndef TOWHEE_MC_MOVE_WRAPPER_H
#define TOWHEE_MC_MOVE_WRAPPER_H

namespace towheewrappers
{

    class TowheeMCMove {

        public:

            TowheeMCMove(double p);

            // Non-API methods
            double getProbability();
            virtual void setup() = 0;

        protected:
            double probability;

    };
}

#endif
