/*
 *  LammpsRegionSphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_REGION_SPHERE_WRAPPER_H
#define LAMMPS_REGION_SPHERE_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsRegion.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsRegionSphere : public virtual LammpsRegion {

        public:
            /**
              * Used to issue a native Lammps simulation region ... sphere
              * command.  Uses the units box keyword.
              * @param sim Simulation pertaining to this region.
              * @param center Vector containing Lammps simulation region
              *               x, y and z parameters (center of sphere).
              * @param radius Lammps simulation region radius parameter.
              * Native Lammps calls :
              *   region ... sphere ... units box
              */
            LammpsRegionSphere(IAPISimulation *sim,
                               IAPIVector *center,
                               double radius);

    };
}

#endif
