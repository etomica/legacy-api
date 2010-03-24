/*
 *  TowheeRandom.h
 *  API Glue
 *
 */

#ifndef TOWHEE_RANDOM_WRAPPER_H
#define TOWHEE_RANDOM_WRAPPER_H

#include "IAPIRandom.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeRandom : public virtual IAPIRandom {

        public:
            /**
              * Create a new random number generator.  The random number
              * generator is contained within the native Towee simulation.
              * @param allowRestart Flag indicating whether the random
              *                     number generator should allow a restart
              *                     (see towhee documentation for more
              *                     information).  Calls
              *                     twh_random_allow_restart if allowRestart
              *                     is true and twh_init_random_single if
              *                     allowRestart is false.
              */
            TowheeRandom(bool allowRestart);
            /**
              * Create a new random number generator.  The random number
              * generator is contained within the native Towee simulation.
              * @param allowRestart Flag indicating whether the random
              *                     number generator should allow a restart
              *                     (see towhee documentation for more
              *                     information).  Calls
              *                     twh_random_allow_restart if allowRestart
              *                     is true and twh_init_random_single if
              *                     allowRestart is false.
              * @param seed Random number generator seed.  Is passed into the
              *             native towhee simulation (twh_randomseed).
              */
            TowheeRandom(bool allowRestart, long seed);
            /**
              * Create a new random number generator.  The random number
              * generator is contained within the native Towee simulation.
              * @param allowRestart Flag indicating whether the random
              *                     number generator should allow a restart
              *                     (see towhee documentation for more
              *                     information).  Calls
              *                     twh_random_allow_restart if allowRestart
              *                     is true and twh_init_random_single if
              *                     allowRestart is false.
              * @param seed Random number generator seed.  Is passed into the
              *             native towhee simulation (twh_randomseed).
              * @param luxLevel Sets the random number generator luxury
              *                 level in the native Towhee simulation
              *                 (thw_random_luxlevel).  See towhee
              *                 documentation for more information.
              */
            TowheeRandom(bool allowRestart, long seed, int luxLevel);

            // API Compliance
            /**
              * This method is not implemented.
              */
            double nextDouble();
            /**
              * This method is not implemented.
              */
            int nextInt(int maxInt);
            /**
              * This method is not implemented.
              */
            double nextGaussian();


    };
}
#endif
