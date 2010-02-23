/*
 *  LammpsSpace.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPACE_WRAPPER_H
#define LAMMPS_SPACE_WRAPPER_H

#include "IAPIVectorMutable.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsSpace {

        public:
            LammpsSpace(int dim);

            int getD();
            IAPIVectorMutable *makeVector();
            IAPIVectorMutable *makeVector(double ***vals);
            IAPIVectorMutable *makeVector(double ***vals, int idx);

        private:
            int D;
    };
}
#endif
