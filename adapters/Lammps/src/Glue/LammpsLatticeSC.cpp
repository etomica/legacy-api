/*
 *  LammpsLatticeSC.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeSC.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeSC::LATTICE_NAME = "sc";

    LammpsLatticeSC::LammpsLatticeSC(IAPISimulation *sim, double sc) :
                                     LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
