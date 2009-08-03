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
            LammpsRegionSphere(IAPISimulation *sim,
                               IAPIVector *center,
                               double radius);

    };
}

#endif
