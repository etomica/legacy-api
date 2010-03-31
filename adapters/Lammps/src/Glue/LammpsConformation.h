/*
 *  LammpsConformation.h
 *  API Glue
 *
 */

#ifndef LAMMPS_CONFORMATION_WRAPPER_H
#define LAMMPS_CONFORMATION_WRAPPER_H

#include "IAPISimulation.h"
#include "LammpsInterfaceConformation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsConformation : public virtual LammpsInterfaceConformation {

        public:
            /**
              * @param sim The simulation that holds the boundary.
              */
            LammpsConformation(IAPISimulation *sim);

            // API Compliance
            void initializePositions(IAPIAtomList *as);

        private:
            LammpsSimulation *mSim;
    };
}

#endif
