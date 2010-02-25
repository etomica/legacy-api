/*
 *  LammpsBoundaryFixed.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARYFIXED_WRAPPER_H
#define LAMMPS_BOUNDARYFIXED_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBoundaryFixed : public LammpsBoundary {

        public:
            LammpsBoundaryFixed(LammpsSimulation *sim);

            // API Compliance
            virtual bool getPeriodicity(int d);


    };
}

#endif
