/*
 *  GlotzillaRandom.h
 *  API Glue
 *
 */

#ifndef GLOTZ_RANDOM_WRAPPER_H
#define GLOTZ_RANDOM_WRAPPER_H

#include <glotzmd.h>

#include "IAPIRandom.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaRandom is a random number generator.  It hold a Glotzilla
      * native random number generator (glotzmath::StdLIbErand48) which
      * implements the random number generator functionality.  This class
      * is just an API "overlay".
      */
    class GlotzillaRandom : public virtual IAPIRandom {

        public:
            /**
              *  Creates a random number generator.  This object is a mirror
              *  for an instance of one of Glotzilla's random number generators
              *  (glotzmath::StdLibErand48).
              */
            GlotzillaRandom();

            // API Compliance
            double nextDouble();
            int nextInt(int maxInt);
            double nextGaussian();

        protected:
            glotzmath::RandomNumberGenerator *mRand;

    };
}
#endif
