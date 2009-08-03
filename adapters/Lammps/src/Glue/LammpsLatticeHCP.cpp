/*
 *  LammpsLatticeHCP.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLatticeHCP.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    const char *const LammpsLatticeHCP::LATTICE_NAME = "hcp";

    LammpsLatticeHCP::LammpsLatticeHCP(IAPISimulation *sim, double sc) :
                                        LammpsLattice(sim, sc, LATTICE_NAME) {
    }

}
