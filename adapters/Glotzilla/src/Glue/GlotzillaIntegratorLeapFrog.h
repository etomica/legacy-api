/*
 *  GlotzillaIntegratorLeapFrog.h
 *  API Glue
 *
 */


#ifndef GLOTZ_LFINTEGERATOR_WRAPPER_H
#define GLOTZ_LFINTEGERATOR_WRAPPER_H

#include <glotzmd.h>

#include "IAPISimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaIntegratorLeapFrog here.
      */
    class GlotzillaIntegratorLeapFrog : public GlotzillaIntegrator {

        public:
            /**
              * GlotzillaIntegratorLeapFrog constructor creates a
              * leap frog integrator.  It holds an instance of a Glotzilla
              * native leap frog integrator
              * (glotzmd::VelocityVerletIntegrator).
              * @param sim Simulation that the integrator belongs to.
              */
            GlotzillaIntegratorLeapFrog(IAPISimulation *sim);
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
            glotzmd::LeapFrogIntegrator *mIntegrator;

    };
}
#endif
