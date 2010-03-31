/*
 *  LammpsNVEAsphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVE_ASPHERE_WRAPPER_H
#define LAMMPS_NVE_ASPHERE_WRAPPER_H

#include "LammpsNVE.h"

namespace lammpswrappers
{

    class LammpsNVEAsphere : public LammpsNVE {

        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nve/asphere fix.
              */
            LammpsNVEAsphere();

    };
}

#endif
