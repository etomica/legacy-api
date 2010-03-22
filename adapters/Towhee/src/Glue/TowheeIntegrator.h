/*
 *  TowheeIntegrator.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INTEGRATOR_WRAPPER_H
#define TOWHEE_INTEGRATOR_WRAPPER_H

#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
#include "TowheeIntegratorEventManager.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegrator : public virtual IAPIIntegrator {

        public:

            TowheeIntegrator();

            // API Compliance
            /**
              * Performs the elementary integration step, such as a
              * molecular dynamics time step, or a Monte Carlo trial by
              * calling into the native Towhee simulation (main_do_mc_move).
              */
            void doStep();
            /**
              * This method is not implemented.
              */
            long long getStepCount();
            /**
              * This method is not implemented.
              */
            void reset();
            /**
              * This method is not implemented.
              */
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

        protected:
            /**
              * Sets the temperature of the simulation by calling into the
              * native Towhee simulation (twh_temperature).
              */
            void setTemperature(double temp);

        private:
            TowheeIntegratorEventManager *mEventManager;
    };
}

#endif
