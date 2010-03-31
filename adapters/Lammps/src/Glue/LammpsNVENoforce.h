/*
 *  LammpsNVENoforce.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVE_FORCE_WRAPPER_H
#define LAMMPS_NVE_FORCE_WRAPPER_H

#include "LammpsNVE.h"

namespace lammpswrappers
{

    class LammpsNVENoforce : public LammpsNVE {

        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nve/noforce fix.
              */
            LammpsNVENoforce();

    };
}

#endif
