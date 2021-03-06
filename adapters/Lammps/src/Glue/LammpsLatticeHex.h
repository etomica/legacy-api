/*
 *  LammpsLatticeHex.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICEHEX_WRAPPER_H
#define LAMMPS_LATTICEHEX_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeHex : public virtual LammpsLattice {

        public:
            /**
              * Create a Hex lattice (native Lammps simulation lattice).
              * @param sim Simulation that contains the integrator.
              * @param sc Scale factor between lattice and simulation box.
              */
            LammpsLatticeHex(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
