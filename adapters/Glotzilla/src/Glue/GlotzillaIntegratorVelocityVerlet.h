/*
 *  GlotzillaIntegratorVelocityVerlet.h
 *  API Glue
 *
 */


#ifndef GLOTZ_VVINTEGERATOR_WRAPPER_H
#define GLOTZ_VVINTEGERATOR_WRAPPER_H

#include <glotzmd.h>

#include "IAPISimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaIntegratorVelocityVerlet here.
      */
    class GlotzillaIntegratorVelocityVerlet : public GlotzillaIntegrator {

        public:
            /**
              * GlotzillaIntegratorVelocityVerlet constructor creates a
              * velocity verlet integrator.  It holds an instance of
              * a Glotzilla native velocity verlet integrator
              * (glotzmd::VelocityVerletIntegrator).
              * @param sim Simulation that the integrator belongs to.
              */
            GlotzillaIntegratorVelocityVerlet(IAPISimulation *sim);
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
            glotzmd::VelocityVerletIntegrator *mIntegrator;

    };
}
#endif
