/*
 *  LammpsLatticeSQ.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICESQ_WRAPPER_H
#define LAMMPS_LATTICESQ_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsLattice.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsLatticeSQ : public virtual LammpsLattice {

        public:
            LammpsLatticeSQ(IAPISimulation *sim, double sc);

        private:
            static const char* const LATTICE_NAME;
    };
}

#endif
