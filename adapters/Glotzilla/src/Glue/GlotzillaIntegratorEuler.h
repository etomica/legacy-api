/*
 *  GlotzillaIntegratorEuler.h
 *  API Glue
 *
 */


#ifndef GLOTZ_EULERINTEGERATOR_WRAPPER_H
#define GLOTZ_EULERINTEGERATOR_WRAPPER_H

#include <glotzmd.h>

#include "IAPISimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaIntegratorEuler : public GlotzillaIntegrator {

        public:
            /**
              * GlotzillaIntegratorEuler constructor creates a
              * euler integrator.  It holds an instance of a Glotzilla
              * native euler integrator (glotzmd::EulerIntegrator).
              * @param sim Simulation that the integrator belongs to.
              */
            GlotzillaIntegratorEuler(IAPISimulation *sim);
            /**
              * Defines the actions taken by the integrator to reset itself,
              * such as required if a perturbation is applied to the
              * simulated box (e.g., addition or deletion of a molecule).
              * Also invoked when the integrator is started or initialized.
              */
            void reset();
            /**
              * Initializes the integrator.  This method should be called before calling
              * doStep.  This method resets the step counter.
              */
            void initialize();

        protected:
            glotzmd::EulerIntegrator *mIntegrator;

    };
}
#endif
