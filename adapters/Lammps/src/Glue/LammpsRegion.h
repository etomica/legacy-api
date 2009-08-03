/*
 *  LammpsRegion.h
 *  API Glue
 *
 */

#ifndef LAMMPS_REGION_WRAPPER_H
#define LAMMPS_REGION_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsRegion {

        public:
            LammpsRegion(IAPISimulation *sim);
            void fillAtoms(IAPISpecies *species);
            char *getRegionID();
            IAPISpecies *getSpecies();

        protected:
            char *mRegionID;
            LammpsSimulation *mSim;
            IAPISpecies *mSpecies;
    };
}

#endif
