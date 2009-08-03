/*
 *  LammpsNVTAsphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVT_ASPHERE_WRAPPER_H
#define LAMMPS_NVT_ASPHERE_WRAPPER_H

#include "LammpsNVT.h"

namespace lammpswrappers
{

    class LammpsNVTAsphere : public LammpsNVT {
        public:
            LammpsNVTAsphere(double tStart, double tStop, double tDamp, double dragVal);

    };
}

#endif
