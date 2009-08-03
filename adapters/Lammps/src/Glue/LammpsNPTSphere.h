/*
 *  LammpsNPTSphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NPT_SPHERE_WRAPPER_H
#define LAMMPS_NPT_SPHERE_WRAPPER_H

#include "LammpsNPT.h"

namespace lammpswrappers
{

    class LammpsNPTSphere : public LammpsNPT {
        public:
            LammpsNPTSphere(double tStart, double tStop, double tDamp);

    };
}

#endif
