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

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryPeriodic : public LammpsBoundary {

        public:
            /**
              * Create a boundary with a periodic style in each dimension.
              * @param sim The simulation that holds the boundary.
              */
            LammpsBoundaryPeriodic(IAPISimulation *sim);

            // API Compliance
            void setBoxSize(IAPIVector *v);
            void nearestImage(IAPIVectorMutable *v);
            IAPIVector *centralImage(IAPIVector *v);
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps boundary command for a
              * periodic bound in each dimenstion
              * Native Lammps calls :
              *   boundary p p p
              */
            virtual void lammpsSetup();

        private:
            IAPIVectorMutable *dimensions;
            IAPIVectorMutable *dimensionsHalf;
            IAPIVectorMutable *mEdge;

    };
}

#endif
