/*
 *  LammpsRegionBlock.h
 *  API Glue
 *
 */

#ifndef LAMMPS_REGION_BLOCK_WRAPPER_H
#define LAMMPS_REGION_BLOCK_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsRegion.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsRegionBlock : public virtual LammpsRegion {

        public:
            LammpsRegionBlock(IAPISimulation *sim,
                              IAPIVector *regionMin,
                              IAPIVector *regionMax);

    };
}

#endif
