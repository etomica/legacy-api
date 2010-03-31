/*
 *  LammpsRegionPrism.h
 *  API Glue
 *
 */

#ifndef LAMMPS_REGION_PRISM_WRAPPER_H
#define LAMMPS_REGION_PRISM_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsRegion.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsRegionPrism : public virtual LammpsRegion {

        public:
            /**
              * Used to issue a native Lammps simulation region ... prism
              * command.  Uses the units box keyword.
              * @param sim Simulation pertaining to this region.
              * @param min Vector containing Lammps simulation region
              *            lo parameters. 
              * @param max Vector containing Lammps simulation region
              *            hi parameters. 
              * @param xy Lammps simulation region xy parameter.
              * @param xz Lammps simulation region xz parameter.
              * @param yz Lammps simulation region yz parameter.
              * Native Lammps calls :
              *   region ... prism ... units box
              */
            LammpsRegionPrism(IAPISimulation *sim,
                               IAPIVector *min,
                               IAPIVector *max,
                               double xy, double xz, double yz);

    };
}

#endif
