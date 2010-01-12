/*
 *  LammpsRandom.h
 *  API Glue
 *
 */

#ifndef LAMMPS_RANDOM_WRAPPER_H
#define LAMMPS_RANDOM_WRAPPER_H

#include "random_mars.h"

#include "IAPIRandom.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsRandom : public LAMMPS_NS::RanMars, public virtual IAPIRandom {

        public:
            LammpsRandom(LammpsSimulation *sim, int seed);

            // API Compliance
            double nextDouble();
            int nextInt(int maxInt);
            double nextGaussian();


    };
}
#endif
