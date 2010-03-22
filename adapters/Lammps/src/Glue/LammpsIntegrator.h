/*
 *  LammpsIntegrator.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_WRAPPER_H
#define LAMMPS_INTEGERATOR_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
#include "LammpsMomentum.h"
#include "LammpsNVE.h"
#include "LammpsNVT.h"
#include "LammpsNPT.h"
#include "LammpsNPH.h"
#include "LammpsSimulation.h"
#include "LammpsTemperatureRescale.h"

using namespace molesimAPI;
using namespace LAMMPS_NS;

namespace lammpswrappers
{

    class LammpsIntegrator : public virtual IAPIIntegrator {

        public:			
            LammpsIntegrator(IAPISimulation *sim);

            // API Compliance
            /**
              * Performs the elementary integration step, such as a
              * molecular dynamics time step, or a Monte Carlo trial.
              * Native Lammps calls :
              *    run
              */
            void doStep();
            long long getStepCount();
            /**
              * This method is not implemented.
              */
            void reset();
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

            // Non-API methods
            /**
              * Native Lammps calls :
              *    fix
              *
              * @param nve
              */
            void setNVE(LammpsNVE *nve); // ARG LIST COMPELTE
            /**
              * Native Lammps calls :
              *    fix
              *    compute_modify
              *
              * @param nvt
              */
            void setNVT(LammpsNVT *nvt); // ARG LIST COMPELTE
            /**
              * Native Lammps calls :
              *    fix
              *
              * @param npt
              */
            void setNPT(LammpsNPT *npt); // ARG LIST NOT COMPLETE
            /**
              * Native Lammps calls :
              *    fix
              *
              * @param nph
              */
            void setNPH(LammpsNPH *nph); // ARG LIST NOT COMPELTE

            void setTempRescale(LammpsTemperatureRescale *rescale);
            void setMomentum(LammpsMomentum *m);
            void setTimestep(double ts);
            /**
              * Performs the elementary integration step, such as a
              * molecular dynamics time step, or a Monte Carlo trial.
              * Performs multiple steps.
              * Native Lammps calls :
              *    run
              *
              * @param nSteps Number of steps to perform.
              */
            void doSteps(int nSteps);


        protected:
            LammpsSimulation *mSimulation;
            bool initialized;
            virtual void lammpsSetup();
            double timeStep;

        private:
            long long stepCount;
            IAPIIntegratorEventManager *mEventManager;

            // Fix type parameters
            static const int NONE;
            static const int NVE;
            static const int NVT;
            static const int NPT;
            static const int NPH;
            int fixType;

            LammpsNVE *fixNVE;
            LammpsNVT *fixNVT;
            LammpsNPT *fixNPT;
            LammpsNPH *fixNPH;

            // temperature rescale fix
            LammpsTemperatureRescale *tempRescale;
            LammpsMomentum *momentum;


    };
}
#endif
