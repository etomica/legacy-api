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
            LammpsRandom(IAPISimulation *sim, int seed);

            // API Compliance
            double nextDouble();
            int nextInt(int maxInt);
            double nextGaussian();

        protected:

    };
}
#endif
