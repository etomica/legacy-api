/*
 *  LammpsLatticeFCC.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICEFCC_WRAPPER_H
#define LAMMPS_LATTICEFCC_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeFCC : public virtual LammpsLattice {

        public:
            LammpsLatticeFCC(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
