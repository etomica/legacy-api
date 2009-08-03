/*
 *  LammpsBoundaryDeformable.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_DEFORMABLE_WRAPPER_H
#define LAMMPS_BOUNDARY_DEFORMABLE_WRAPPER_H


#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsBoundary.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryDeformable : public LammpsBoundary {

        public:
            LammpsBoundaryDeformable(IAPISimulation *sim, int steps,
                                  IAPIVector *vecLower, IAPIVector *vecUpper);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            virtual void lammpsSetup();

        private:
            int numSteps;
            IAPIVectorMutable *mVecLower;
            IAPIVectorMutable *mVecUpper;
            char *mFixID;

    };
}

#endif
