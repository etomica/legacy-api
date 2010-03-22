/*
 *  IAPIIntegrator.h
 *  API Glue
 *
 */


#ifndef API_IINTEGERATOR_WRAPPER_H
#define API_IINTEGERATOR_WRAPPER_H

#include "IAPIIntegratorEventManager.h"

namespace molesimAPI
{

    class IAPIIntegrator
    {
        public:
            /**
              * Performs the elementary integration step, such as a
              * molecular dynamics time step, or a Monte Carlo trial.
              */
            virtual void doStep() = 0;
            /**
              * @return Returns the number of steps performed by the
              *         integrator since it was initialized.
              */
            virtual long long getStepCount() = 0;
            /**
              * Defines the actions taken by the integrator to reset itself,
              * such as required if a perturbation is applied to the
              * simulated box (e.g., addition or deletion of a molecule).
              * Also invoked when the integrator is started or initialized.
              */
            virtual void reset() = 0;
            /**
              * This method resets the step counter.
              */
            virtual void resetStepCount() = 0;
            /**
              * @return Returns the event manager for the integrator.
              */
            virtual IAPIIntegratorEventManager *getEventManager() = 0;

    };
}
#endif
