/*
 *  LammpsNPTAsphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NPT_ASPHERE_WRAPPER_H
#define LAMMPS_NPT_ASPHERE_WRAPPER_H

#include "LammpsNPT.h"

namespace lammpswrappers
{

    class LammpsNPTAsphere : public LammpsNPT {
        public:
            LammpsNPTAsphere(double tStart, double tStop, double tDamp);

    };
}

#endif
