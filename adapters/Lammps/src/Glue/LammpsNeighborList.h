
/*
 *  LammpsNeighborList.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NBR_WRAPPER_H
#define LAMMPS_NBR_WRAPPER_H

#include "IAPISimulation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsNeighborList {

        public:
            /**
              * Superclass for lammps neighbor list classes.  An object of
              * this class should not be instantiated.
              * @param sim Simulation pertaining to this neighbor list.
              * @param cutoff extra distance beyond force cutoff
              */
            LammpsNeighborList(IAPISimulation *sim, double cut);

            /**
              * @param val Delay building neighbor list until this many steps
              *            since last build.
              * Native Lammps calls :
              *   neigh_modify delay
              */
            void setDelay(int val);
            /**
              * @param val Build neighbor list every this many steps.
              * Native Lammps calls :
              *   neigh_modify every
              */
            void setEvery(int val);
            /**
              * @param val
              *        0 = always build on 1st step that every and delay are
              *            satisfied
              *        1 = only build if some atom has moved half the skin
              *            distance or more
              * Native Lammps calls :
              *   neigh_modify check
              */
            void setCheck(bool val);
            /**
              * @param val Number of pairs stored in a single neighbor page.
              * Native Lammps calls :
              *   neigh_modify page
              */
            void setPage(int val);
            /**
              * @param val Maximum number of neighbors of one atom.
              * Native Lammps calls :
              *   neigh_modify one
              */
            void setOne(int val);
            /**
              * @param val Bin size for neighbor list construction.
              * Native Lammps calls :
              *   neigh_modify binsize
              */
            void setBinSize(int val);

        protected:
            LammpsSimulation *mSim;
            double cutoff;
    };
}

#endif
