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
            /**
              * Change the volume of the simulation box (using native Lammps
              * simulation fix ... deform command).
              * @param sim The simulation that holds the boundary.
              * @param steps perform box deformation every this many timesteps
              * @param vecLower Vector containing boundary style for lower
              *                 bounds.
              * @param vecUpper Vector containing boundary style for upper y
              *                 bounds.
              */
            LammpsBoundaryDeformable(IAPISimulation *sim, int steps,
                                  IAPIVector *vecLower, IAPIVector *vecUpper);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps fix deform command using
              * the parameters stored in the class instance. Style is final.
              * Native Lammps calls :
              *   fix ... all deform
              */
            virtual void lammpsSetup();

        private:
            int numSteps;
            IAPIVectorMutable *mVecLower;
            IAPIVectorMutable *mVecUpper;
            char *mFixID;

    };
}

#endif
