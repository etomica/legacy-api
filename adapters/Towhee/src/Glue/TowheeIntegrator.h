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
            void doStep();
            long long getStepCount();
            void reset();
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

        protected:
            void setTemperature(double temp);

        private:
            TowheeIntegratorEventManager *mEventManager;
    };
}

#endif
