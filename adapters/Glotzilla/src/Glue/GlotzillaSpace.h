/*
 *  GlotzillaSpace.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPACE_WRAPPER_H
#define GLOTZ_SPACE_WRAPPER_H

#include <glotzmd.h>

#include "IAPIVectorMutable.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * The GlotzillaSpace is a vector factory.  It is aware of the
      * simulation dimension and is able to make vectors of that
      * dimension.
      */
    class GlotzillaSpace {

        public:
            /**
              * Create a Glotzilla space of the given dimension.
              * @param dim Dimension of which to create space.
              */
            GlotzillaSpace(int dim);

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
              * @return Returns a new vector of the dimension held by the
              *         space.  The vector is mutable.  The vector
              *         constructor requiring a natvie Glotzilla vector
              *         (glotzmath::glotz_vec) is called.
              */
            IAPIVectorMutable *makeVector(glotzmath::glotz_vec *gVec);

        private:
            int D;
    };
}
#endif
