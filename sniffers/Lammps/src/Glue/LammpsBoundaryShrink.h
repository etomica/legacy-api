/*
 *  LammpsBoundaryShrink.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_SHRINK_WRAPPER_H
#define LAMMPS_BOUNDARY_SHRINK_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBoundaryShrink : public LammpsBoundary {

        public:
            LammpsBoundaryShrink(LammpsSimulation *sim);

            // API Compliance
            virtual bool getPeriodicity(int d);

    };
}

#endif
