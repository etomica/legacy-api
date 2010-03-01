/*
 *  TowheePotentialMaster.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheePotentialMaster.h"

namespace towheewrappers
{

    /*
     * addForceField()
     */
    void TowheePotentialMaster::addForceField(TowheeForceField *ff) {
        mForceField.push_back(ff);
    }

    /*
     * getForceFieldCount()
     */
    int TowheePotentialMaster::getForceFieldCount() {
        return mForceField.size();
    }

    /*
     * getForceField()
     */
    TowheeForceField *TowheePotentialMaster::getForceField(int idx) {
        return mForceField.at(idx);
    }

}
