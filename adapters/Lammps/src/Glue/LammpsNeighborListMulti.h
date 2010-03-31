
/*
 *  LammpsNeighborListMulti.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NBR_MULTI_WRAPPER_H
#define LAMMPS_NBR_MULTI_WRAPPER_H

#include "IAPISimulation.h"
#include "LammpsNeighborList.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsNeighborListMulti : public LammpsNeighborList {

        public:
            /**
              * Create a neighbor list that uses the multi algorithm.
              * Native Lammps calls :
              *   neighbor ... multi
              *
              * @param sim Simulation pertaining to this neighbor list.
              * @param cutoff extra distance beyond force cutoff
              */
            LammpsNeighborListMulti(IAPISimulation *sim, double cutoff);

    };
}

#endif
