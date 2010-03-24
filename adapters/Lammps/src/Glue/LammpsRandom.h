/*
 *  LammpsRandom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_RANDOM_WRAPPER_H
#define LAMMPS_RANDOM_WRAPPER_H

#include "random_mars.h"

#include "IAPIRandom.h"
#include "IAPISimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsRandom : public LAMMPS_NS::RanMars, public virtual IAPIRandom {

        public:
            /**
              * Create a new random number generator.  The random number
              * generator is contained within the native Towee simulation.
              * @param sim Simulation that the random number generator is
              *            a part of.
              * @param seed Random number generator seed.  Is passed into the
              *             native lammps simulation.
              */
            LammpsRandom(IAPISimulation *sim, int seed);

            // API Compliance
            /**
              * Gets the random number directly from the native Lammps
              * simulation.
              * @return Returns a pseudorandom double, uniformly distributed
              * between 0.0 (inclusive) and 1.0 (exclusive).
              */
            double nextDouble();
            /**
              * This method is not implemented.
              */
            int nextInt(int maxInt);
            /**
              * Gets the random number directly from the native Lammps
              * simulation.
              * @return Returns a pseudorandom double, Gaussian ("normally")
              * distributed value with mean 0.0 and standard deviation 1.0.
              */
            double nextGaussian();

        protected:

    };
}
#endif
