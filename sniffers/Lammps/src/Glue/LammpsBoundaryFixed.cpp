/*
 *  LammpsBoundaryFixed.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryFixed.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryFixed::LammpsBoundaryFixed(LammpsSimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * getPeriodicity()
     */
    bool LammpsBoundaryFixed::getPeriodicity(int d) {
        return false;
    }

}

