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
            /**
              * A superclass for specific lammps regions.  An instance of
              * this class should not be instantiated.  Regions are used
              * to issue a native Lammps region command.
              * @param sim Simulation pertaining to this region.
              */
            LammpsRegion(IAPISimulation *sim);

            /**
              * @param species Species with which to fill the region with.
              *                The species must be an instance of
              *                LammpsSpeciesSpheres.
              */
            void fillAtoms(IAPISpecies *species);
            /**
              * @return Returns the region id, as used in the native Lammps
              *         simulation region command, as a string, for this
              *         region.
              */
            char *getRegionID();
            /**
              * @return Returns the species with which the region is filled
              *         with.
              */
            IAPISpecies *getSpecies();

        protected:
            char *mRegionID;
            LammpsSimulation *mSim;
            IAPISpecies *mSpecies;
    };
}

#endif
