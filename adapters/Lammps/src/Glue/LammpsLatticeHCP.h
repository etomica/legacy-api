/*
 *  LammpsLatticeHCP.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICEHCP_WRAPPER_H
#define LAMMPS_LATTICEHCP_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeHCP : public virtual LammpsLattice {

        public:
            /**
              * Create a HCP lattice (native Lammps simulation lattice).
              * @param sim Simulation that contains the integrator.
              * @param sc Scale factor between lattice and simulation box.
              */
            LammpsLatticeHCP(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
