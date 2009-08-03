/*
 *  LammpsSpace.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPACE_WRAPPER_H
#define LAMMPS_SPACE_WRAPPER_H

#include "IAPIVectorMutable.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSpace {

        public:
            LammpsSpace(int dim);

            int getD();
            IAPIVectorMutable *makeVector();
            IAPIVectorMutable *makeVector(double *vals);

        private:
            int D;
    };
}
#endif
