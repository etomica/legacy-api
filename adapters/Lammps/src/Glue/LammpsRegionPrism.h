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
            LammpsRegionPrism(IAPISimulation *sim,
                               IAPIVector *min,
                               IAPIVector *max,
                               double xy, double xz, double yz);

    };
}

#endif
