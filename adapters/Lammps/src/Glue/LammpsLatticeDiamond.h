/*
 *  LammpsLatticeDiamond.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICEDiamond_WRAPPER_H
#define LAMMPS_LATTICEDiamond_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeDiamond : public virtual LammpsLattice {

        public:
            /**
              * Create a Diamond lattice (native Lammps simulation lattice).
              * @param sim Simulation that contains the integrator.
              * @param sc Scale factor between lattice and simulation box.
              */
            LammpsLatticeDiamond(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
