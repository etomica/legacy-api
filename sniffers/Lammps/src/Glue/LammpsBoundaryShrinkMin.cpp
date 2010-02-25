/*
 *  LammpsBoundaryShrinkMin.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryShrinkMin.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryShrinkMin::LammpsBoundaryShrinkMin(LammpsSimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * getPeriodicity()
     */
    bool LammpsBoundaryShrinkMin::getPeriodicity(int d) {
        return false;
    }

}

