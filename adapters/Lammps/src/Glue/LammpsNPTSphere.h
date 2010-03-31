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
            /**
              * Class that stores parameters for the native Lammps
              * simulation npt/sphere fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              */
            LammpsNPTSphere(double tStart, double tStop, double tDamp);

    };
}

#endif
