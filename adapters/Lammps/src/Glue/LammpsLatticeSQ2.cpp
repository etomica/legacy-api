/*
 *  LammpsLatticeSQ2.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeSQ2.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeSQ2::LATTICE_NAME = "sq2";

    LammpsLatticeSQ2::LammpsLatticeSQ2(IAPISimulation *sim, double sc) :
                                    LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
