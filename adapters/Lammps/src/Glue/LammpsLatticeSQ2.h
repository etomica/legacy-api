/*
 *  LammpsLatticeSQ2.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICESQ2_WRAPPER_H
#define LAMMPS_LATTICESQ2_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeSQ2 : public virtual LammpsLattice {

        public:
            LammpsLatticeSQ2(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
