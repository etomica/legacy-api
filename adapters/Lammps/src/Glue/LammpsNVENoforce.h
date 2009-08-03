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
            LammpsNVENoforce();

    };
}

#endif
