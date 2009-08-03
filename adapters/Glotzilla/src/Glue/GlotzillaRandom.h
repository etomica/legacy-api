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
            /**
              * @return Returns a pseudorandom double, uniformly distributed
              * between 0.0 (inclusive) and 1.0 (exclusive).
              */
            double nextDouble();
            /**
             * @param Maximum value of the returned value
             * @return Returns a pseudorandom integer, uniformly distributed
             * between 0 (inclusive) and maxInt (exclusive).
             */
            int nextInt(int maxInt);
            /**
              * @return Returns a pseudorandom double, Gaussian ("normally")
              * distributed value with mean 0.0 and standard deviation 1.0.
              */
            double nextGaussian();

        protected:
            glotzmath::RandomNumberGenerator *mRand;

    };
}
#endif
