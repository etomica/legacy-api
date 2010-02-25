/*
 *  LammpsBoundaryShrink.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryShrink.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryShrink::LammpsBoundaryShrink(LammpsSimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * getPeriodicity()
     */
    bool LammpsBoundaryShrink::getPeriodicity(int d) {
        return false;
    }

}

