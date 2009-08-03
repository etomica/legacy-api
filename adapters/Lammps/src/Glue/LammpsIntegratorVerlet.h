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
            LammpsIntegratorVerlet(IAPISimulation *sim);

        protected:
            virtual void lammpsSetup();

    };
}
#endif
