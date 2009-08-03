/*
 *  LammpsLatticeHex.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeHex.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeHex::LATTICE_NAME = "hex";

    LammpsLatticeHex::LammpsLatticeHex(IAPISimulation *sim, double sc) :
                                     LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
