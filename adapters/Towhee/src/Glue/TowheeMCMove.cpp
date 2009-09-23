/*
 *  TowheeMCMove.cpp
 *  API Glue
 *
 *
 */

#include "TowheeMCMove.h"

namespace towheewrappers
{

    TowheeMCMove::TowheeMCMove(double p) {
        probability = p;
    }

    /*
     * getProbability()
     */
    double TowheeMCMove::getProbability() {
        return probability;
    }

}
