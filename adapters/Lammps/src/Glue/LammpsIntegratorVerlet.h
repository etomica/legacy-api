/*
 *  LammpsIntegratorVerlet.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATORVERLET_WRAPPER_H
#define LAMMPS_INTEGERATORVERLET_WRAPPER_H

#include "IAPIBox.h"
#include "LammpsIntegrator.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsIntegratorVerlet : public LammpsIntegrator {

        public:
            /**
              * Create an integrator (native Lammps simulation run_style) of
              * type verlet.
              * @param sim Simulation that contains the integrator.
              */
            LammpsIntegratorVerlet(IAPISimulation *sim);

        protected:
            /**
              * Native Lammps calls :
              *   run_style verlet
              *
              */
            virtual void lammpsSetup();

    };
}
#endif
