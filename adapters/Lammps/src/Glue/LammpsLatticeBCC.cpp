/*
 *  LammpsLatticeBCC.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeBCC.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeBCC::LATTICE_NAME = "bcc";

    LammpsLatticeBCC::LammpsLatticeBCC(IAPISimulation *sim, double sc) :
                                      LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
