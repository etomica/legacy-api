/*
 *  LammpsLatticeSC.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICESC_WRAPPER_H
#define LAMMPS_LATTICESC_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeSC : public virtual LammpsLattice {

        public:
            /**
              * Create a SC lattice (native Lammps simulation lattice).
              * @param sim Simulation that contains the integrator.
              * @param sc Scale factor between lattice and simulation box.
              */
            LammpsLatticeSC(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
