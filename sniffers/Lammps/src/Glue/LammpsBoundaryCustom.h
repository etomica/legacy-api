/*
 *  LammpsBoundaryCustom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_CUSTOM_WRAPPER_H
#define LAMMPS_BOUNDARY_CUSTOM_WRAPPER_H


#include "IAPIVector.h"

#include "LammpsBoundary.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBoundaryCustom : public LammpsBoundary {

        public:
            LammpsBoundaryCustom(LammpsSimulation *sim, int xLower, int xUpper,
                                 int yLower, int yUpper, int zLower, int zUpper);

            // API Compliance
            virtual bool getPeriodicity(int d);

            // Non-API methods
            static const int DEFAULT_TYPE;
            static const int PERIODIC;
            static const int FIXED;
            static const int SHRINK;
            static const int SHRINK_MINIMUM;

        protected:
        private:
            int checkTypeBounds(int type);
            int mXLower;
            int mXUpper;
            int mYLower;
            int mYUpper;
            int mZLower;
            int mZUpper;
    };
}

#endif
