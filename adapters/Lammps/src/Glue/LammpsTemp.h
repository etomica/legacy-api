/*
 *  LammpsTemp.h
 *  API Glue
 *
 */

#ifndef LAMMPS_TEMP_WRAPPER_H
#define LAMMPS_TEMP_WRAPPER_H

#include <vector>
#include <iostream>

#include "lammps.h"

#include "LammpsSimulation.h"


using namespace LAMMPS_NS;

namespace lammpswrappers
{

    class LammpsTemp {

        public:
            LammpsTemp(LammpsSimulation *sim);

        protected:

        private:
    };
}

#endif
