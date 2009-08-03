/*
 *  LammpsLatticeDiamond.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeDiamond.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeDiamond::LATTICE_NAME = "diamond";

    LammpsLatticeDiamond::LammpsLatticeDiamond(IAPISimulation *sim, double sc) :
                                              LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
