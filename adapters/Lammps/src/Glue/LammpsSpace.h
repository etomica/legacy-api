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

    /**
      * The LammpsSpace is a vector factory.  It is aware of the
      * simulation dimension and is able to make vectors of that
      * dimension.
      */
    class LammpsSpace {

        public:
            /**
              * Create a Lammps space of the given dimension.
              * @param dim Dimension of which to create space.
              */
            LammpsSpace(int dim);
            /**
              * @return Returns the dimension of the space
              */
            int getD();
            /**
              * @return Returns a new vector of the dimension held by the
              *         space.  The vector is mutable.  The default
              *         vector constructor is called.
              */
            IAPIVectorMutable *makeVector();
            /**
              * @param vals A pointer(array) to the values for the vector.
              * @return Returns a new vector of the dimension held by the
              *         space.  The vector is mutable.  The vector
              *         returned uses the given double array as its own
              *         storage.  That is to say, modifying the vector
              *         components modifies the given array values directly.
              */
            IAPIVectorMutable *makeVector(double *vals);

        private:
            int D;
    };
}
#endif
