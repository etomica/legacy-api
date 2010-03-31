
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
            /**
              * Create a neighbor list that uses the bin algorithm.
              * Native Lammps calls :
              *   neighbor ... bin
              *
              * @param sim Simulation pertaining to this neighbor list.
              * @param cutoff extra distance beyond force cutoff
              */
            LammpsNeighborListBin(IAPISimulation *sim, double cutoff);

    };
}

#endif
