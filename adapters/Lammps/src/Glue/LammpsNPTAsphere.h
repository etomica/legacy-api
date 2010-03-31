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
            /**
              * Class that stores parameters for the native Lammps
              * simulation npt/asphere fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              */
            LammpsNPTAsphere(double tStart, double tStop, double tDamp);

    };
}

#endif
