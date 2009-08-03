/*
 *  LammpsNVELimit.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVE_LIMIT_WRAPPER_H
#define LAMMPS_NVE_LIMIT_WRAPPER_H

#include "LammpsNVE.h"

namespace lammpswrappers
{

    class LammpsNVELimit : public LammpsNVE {
        public:
            LammpsNVELimit();

    };
}

#endif
