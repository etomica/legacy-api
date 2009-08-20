/*
 *  TowheeSpace.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPACE_WRAPPER_H
#define TOWHEE_SPACE_WRAPPER_H

#include "IAPIVectorMutable.h"

using namespace molesimAPI;

namespace towheewrappers
{

    /**
      * The TowheeSpace is a vector factory.  It is aware of the
      * simulation dimension and is able to make vectors of that
      * dimension.
      */
    class TowheeSpace {

        public:
            /**
              * Create a Towhee space of the given dimension.
              * @param dim Dimension of which to create space.
              */
            TowheeSpace(int dim);

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

        private:
            int D;
    };
}
#endif
