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
            /**
              * Create a boundary with a shrink-wrapped with minimum value
              * style in each dimension.
              * @param sim The simulation that holds the boundary.
              */
            LammpsBoundaryShrinkMin(IAPISimulation *sim);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps boundary command for a
              * shrink-wrapped bound in each dimenstion
              * Native Lammps calls :
              *   boundary m m m
              */
            virtual void lammpsSetup();

    };
}

#endif
