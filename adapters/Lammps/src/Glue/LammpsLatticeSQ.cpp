/*
 *  LammpsLatticeSQ.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeSQ.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeSQ::LATTICE_NAME = "sq";

    LammpsLatticeSQ::LammpsLatticeSQ(IAPISimulation *sim, double sc) :
                                    LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
