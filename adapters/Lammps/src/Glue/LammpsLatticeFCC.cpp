/*
 *  LammpsLatticeFCC.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeFCC.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeFCC::LATTICE_NAME = "fcc";

    LammpsLatticeFCC::LammpsLatticeFCC(IAPISimulation *sim, double sc) :
                                     LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
