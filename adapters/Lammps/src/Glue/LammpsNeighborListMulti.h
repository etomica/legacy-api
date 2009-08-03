
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
            LammpsNeighborListMulti(IAPISimulation *sim, double cutoff);

        protected:
    };
}

#endif
