/*
 *  LammpsLatticeBCC.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICEBCC_WRAPPER_H
#define LAMMPS_LATTICEBCC_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeBCC : public virtual LammpsLattice {

        public:
            LammpsLatticeBCC(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
