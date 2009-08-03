/*
 *  LammpsBoundaryFixed.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARYFIXED_WRAPPER_H
#define LAMMPS_BOUNDARYFIXED_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryFixed : public LammpsBoundary {

        public:
            LammpsBoundaryFixed(IAPISimulation *sim);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            virtual void lammpsSetup();

    };
}

#endif
