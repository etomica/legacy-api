/*
 *  LammpsNVTSphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVT_SPHERE_WRAPPER_H
#define LAMMPS_NVT_SPHERE_WRAPPER_H

#include "LammpsNVT.h"

namespace lammpswrappers
{

    class LammpsNVTSphere : public LammpsNVT {
        public:
            LammpsNVTSphere(double tStart, double tStop, double tDamp, double dragVal);

    };
}

#endif
