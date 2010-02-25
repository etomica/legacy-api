/*
 *  LammpsBoundaryPeriodic.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARYPERIODIC_WRAPPER_H
#define LAMMPS_BOUNDARYPERIODIC_WRAPPER_H


#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

#include "LammpsBoundary.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBoundaryPeriodic : public LammpsBoundary {

        public:
            LammpsBoundaryPeriodic(LammpsSimulation *sim);

            // API Compliance
            void setBoxSize(IAPIVector *v);
            void nearestImage(IAPIVectorMutable *v);
            IAPIVector *centralImage(IAPIVector *v);
            virtual bool getPeriodicity(int d);

        private:

    };
}

#endif
