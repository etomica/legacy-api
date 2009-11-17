/*
 *  TowheeIntegrator.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGERATOR_WRAPPER_H
#define TOWHEE_INTEGERATOR_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
#include "IAPISimulation.h"
#include "TowheeIntegratorEventManager.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * @todo Description of TowheeIntegrator here.
      */
    class TowheeIntegrator : public virtual IAPIIntegrator {

        public:

            TowheeIntegrator();

            void doStep();
            long long getStepCount();
            void reset();
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

            // Non-API methods
            int getEnsemble();

        private:
            TowheeIntegratorEventManager *mEventManager;
    };
}
#endif
