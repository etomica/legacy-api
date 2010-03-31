/*
 *  LammpsNVESphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVE_SPHERE_WRAPPER_H
#define LAMMPS_NVE_SPHERE_WRAPPER_H

#include "LammpsNVE.h"

namespace lammpswrappers
{

    class LammpsNVESphere : public LammpsNVE {

        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nve/sphere fix.
              */
            LammpsNVESphere();

    };
}

#endif
