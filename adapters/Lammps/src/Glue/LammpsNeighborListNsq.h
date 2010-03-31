
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
            /**
              * Create a neighbor list that uses the nsq algorithm.
              * Native Lammps calls :
              *   neighbor ... nsq
              *
              * @param sim Simulation pertaining to this neighbor list.
              * @param cutoff extra distance beyond force cutoff
              */
            LammpsNeighborListNsq(IAPISimulation *sim, double cutoff);

    };
}

#endif
