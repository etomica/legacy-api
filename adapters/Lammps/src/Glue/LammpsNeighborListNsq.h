
/*
 *  LammpsNeighborListNsq.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NBR_BIN_WRAPPER_H
#define LAMMPS_NBR_BIN_WRAPPER_H

#include "IAPISimulation.h"
#include "LammpsNeighborList.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsNeighborListNsq : public LammpsNeighborList {

        public:
            LammpsNeighborListNsq(IAPISimulation *sim, double cutoff);

        protected:
    };
}

#endif
