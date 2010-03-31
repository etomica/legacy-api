/*
 *  LammpsBoundaryShrink.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_SHRINK_WRAPPER_H
#define LAMMPS_BOUNDARY_SHRINK_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryShrink : public LammpsBoundary {

        public:
            /**
              * Create a boundary with a shrink-wrapped style in each
              * dimension.
              * @param sim The simulation that holds the boundary.
              */
            LammpsBoundaryShrink(IAPISimulation *sim);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps boundary command for a
              * shrink-wrapped bound in each dimenstion
              * Native Lammps calls :
              *   boundary s s s
              */
            virtual void lammpsSetup();

    };
}

#endif
