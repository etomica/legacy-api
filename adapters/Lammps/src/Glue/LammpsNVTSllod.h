/*
 *  LammpsNVTSllod.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVT_SLLOD_WRAPPER_H
#define LAMMPS_NVT_SLLOD_WRAPPER_H

#include "LammpsNVT.h"

namespace lammpswrappers
{

    class LammpsNVTSllod : public LammpsNVT {
        public:
            LammpsNVTSllod(double tStart, double tStop, double tDamp, double dragVal);

    };
}

#endif
