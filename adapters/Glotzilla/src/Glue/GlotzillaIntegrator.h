/*
 *  GlotzillaIntegrator.h
 *  API Glue
 *
 */


#ifndef GLOTZ_INTEGERATOR_WRAPPER_H
#define GLOTZ_INTEGERATOR_WRAPPER_H

#include <glotzmd.h>
#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
#include "IAPISimulation.h"

#include "GlotzillaBox.h"
#include "GlotzillaIntegratorEventManager.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaIntegrator here.
      */
    class GlotzillaIntegrator : public virtual IAPIIntegrator {

        public:
            /**
              * GlotzillaIntegrator constructor.  The class is purely virtual
              * so the constructor only gets called from its subclasses.
              * @param sim Simulation that the integrator belongs to.
              */			
            GlotzillaIntegrator(IAPISimulation *sim);

            // API Compliance
            /**
              * Performs the elementary integration step, such as a
              * molecular dynamics time step, or a Monte Carlo trial.
              */
            void doStep();
            /**
              * @return Returns the number of steps performed by the
              *         integrator since it was initialized.
              */
            long long getStepCount();
            /**
              * Defines the actions taken by the integrator to reset itself,
              * such as required if a perturbation is applied to the
              * simulated box (e.g., addition or deletion of a molecule).
              * Also invoked when the integrator is started or initialized.
              */
            void reset() = 0;
            /**
              * This method resets the step counter.
              */
            void resetStepCount();
            /**
              * @return Returns the event manager for the integrator.
              */
            IAPIIntegratorEventManager *getEventManager();

            // Non-API Method
            void setTimestep(double ts);

        protected:
            glotzmd::Simulation* mSimulation;
            bool mInitialized;
            GlotzillaIntegratorEventManager *mEventManager;
    };
}
#endif
