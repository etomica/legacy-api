
/*
 *  LammpsNeighborListBin.h
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

    class LammpsNeighborListBin : public LammpsNeighborList {

        public:
            LammpsNeighborListBin(IAPISimulation *sim, double cutoff);

        protected:
    };
}

#endif
