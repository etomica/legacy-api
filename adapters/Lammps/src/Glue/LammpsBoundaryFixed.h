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
            /**
              * Create a boundary with a fixed style in each dimension.
              * @param sim The simulation that holds the boundary.
              */
            LammpsBoundaryFixed(IAPISimulation *sim);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps boundary command for a
              * fixed bound in each dimenstion
              * Native Lammps calls :
              *   boundary f f f
              */
            virtual void lammpsSetup();

    };
}

#endif
