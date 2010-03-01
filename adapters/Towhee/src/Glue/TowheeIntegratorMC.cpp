/*
 *  TowheeIntegratorMC.cpp
 *  API Glue
 *
 *
 */

#include "TowheeIntegratorMC.h"

namespace towheewrappers
{

    /*
     * addMove()
     */
    void TowheeIntegratorMC::addMove(TowheeMCMove *move) {
        mMoves.push_back(move);
    }

    int TowheeIntegratorMC::getMoveCount() {
        return mMoves.size();
    }

    TowheeMCMove *TowheeIntegratorMC::getMove(int idx) {
        return mMoves.at(idx);
    }


}
