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
            LammpsIntegratorRespa(IAPISimulation *sim, int nLvl, int lvl[]);

        protected:
            virtual void lammpsSetup();

        private:
            int numRespaLevels;
            int *respaLoopFactor;

    };
}
#endif
