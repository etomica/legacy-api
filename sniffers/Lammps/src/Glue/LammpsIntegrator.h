/*
 *  LammpsIntegrator.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_WRAPPER_H
#define LAMMPS_INTEGERATOR_WRAPPER_H

#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;
using namespace LAMMPS_NS;

namespace lammpssnifferwrappers
{

    class LammpsIntegrator : public virtual IAPIIntegrator {

        public:			
            LammpsIntegrator(LammpsSimulation *sim);

            // API Compliance
            void doStep();		
            long long getStepCount();		
            void reset();
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

            // Non-API methods
            void setTimestep(double ts);
            void doSteps(int nSteps);


        protected:
            LammpsSimulation *mSimulation;

        private:
            long long stepCount;
            IAPIIntegratorEventManager *mEventManager;

    };
}
#endif
