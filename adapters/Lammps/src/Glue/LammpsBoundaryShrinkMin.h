/*
 *  LammpsBoundaryShrinkMin.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_SHRINK_MIN_WRAPPER_H
#define LAMMPS_BOUNDARY_SHRINK_MIN_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryShrinkMin : public LammpsBoundary {

        public:
            LammpsBoundaryShrinkMin(IAPISimulation *sim);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            virtual void lammpsSetup();

    };
}

#endif
