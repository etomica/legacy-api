/*
 *  LammpsBoundaryCustom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_CUSTOM_WRAPPER_H
#define LAMMPS_BOUNDARY_CUSTOM_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundaryCustom : public LammpsBoundary {

        public:
            /**
              * Create a boundary with a different style in each dimension.
              * Boundary styles :
              *   PERIODIC       = 0
              *   FIXED          = 1
              *   SHRINK         = 2
              *   SHRINK_MINIMUM = 3
              * @param sim The simulation that holds the boundary.
              * @param xLower Boundary style for lower x bound.
              * @param xUpper Boundary style for upper x bound.
              * @param yLower Boundary style for lower y bound.
              * @param yUpper Boundary style for upper y bound.
              * @param zLower Boundary style for lower z bound.
              * @param zUpper Boundary style for upper z bound.
              */
            LammpsBoundaryCustom(IAPISimulation *sim, int xLower, int xUpper,
                                 int yLower, int yUpper, int zLower, int zUpper);

            // API Compliance
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods
            /**
              * Create and issue the native lammps boundary command using
              * the parameters stored in the class instance.
              * Native Lammps calls :
              *   boundary
              */
            virtual void lammpsSetup();
            static const int DEFAULT_TYPE;
            static const int PERIODIC;
            static const int FIXED;
            static const int SHRINK;
            static const int SHRINK_MINIMUM;

        private:
            char *getBoundaryArgument();
            int checkTypeBounds(int type);
            char *mBoundaryArg;
            int mXLower;
            int mXUpper;
            int mYLower;
            int mYUpper;
            int mZLower;
            int mZUpper;
            static const char* const bondTypes;
    };
}

#endif
