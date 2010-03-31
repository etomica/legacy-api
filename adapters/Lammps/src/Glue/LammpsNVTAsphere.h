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
            /**
              * Class that stores parameters for the native Lammps
              * simulation nvt/asphere fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              * @param drag factor added to thermostat
              */
            LammpsNVTAsphere(double tStart, double tStop, double tDamp, double dragVal);

    };
}

#endif
