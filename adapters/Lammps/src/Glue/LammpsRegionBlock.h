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
            /**
              * Used to issue a native Lammps simulation region ... block
              * command.  Uses the units box keyword.
              * @param sim Simulation pertaining to this region.
              * @param regionMin Vector containing Lammps simulation region
              *                  lo parameters. 
              * @param regionMax Vector containing Lammps simulation region
              *                  hi parameters. 
              * Native Lammps calls :
              *   region ... block ... units box
              */
            LammpsRegionBlock(IAPISimulation *sim,
                              IAPIVector *regionMin,
                              IAPIVector *regionMax);

    };
}

#endif
