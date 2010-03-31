/*
 *  LammpsIntegratorRespa.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATORRESPA_WRAPPER_H
#define LAMMPS_INTEGERATORRESPA_WRAPPER_H

#include "IAPIBox.h"
#include "LammpsIntegrator.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsIntegratorRespa : public LammpsIntegrator {

        public:
            /**
              * Create an integrator (native Lammps simulation run_style) of
              * type respa.
              * @param sim Simulation that contains the integrator.
              * @param nLvl The number of levels of rRESPA
              * @param lvl An array containing the loop factors between
              *            rRESPA levels
              */
            LammpsIntegratorRespa(IAPISimulation *sim, int nLvl, int lvl[]);

        protected:
            /**
              * Native Lammps calls :
              *   run_style respa
              *
              */
            virtual void lammpsSetup();

        private:
            int numRespaLevels;
            int *respaLoopFactor;

    };
}
#endif
