
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
            LammpsNeighborList(IAPISimulation *sim, double cut);

            void setDelay(int val);
            void setEvery(int val);
            void setCheck(bool val);
            void setPage(int val);
            void setOne(int val);
            void setBinSize(int val);

        protected:
            LammpsSimulation *mSim;
            double cutoff;
    };
}

#endif
