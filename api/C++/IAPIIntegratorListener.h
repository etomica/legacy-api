/*
 *  IAPIIntegratorListener.h
 *  API Glue
 *
 */


#ifndef API_IINTEGERATOR_LISTENER_WRAPPER_H
#define API_IINTEGERATOR_LISTENER_WRAPPER_H

#include "IAPIIntegratorEvent.h"

namespace molesimAPI
{

    class IAPIIntegratorListener
    {
        public:
            /**
              * The listener method called when the integrator is
              * initializeing.
              * @param event Information relating to integrator event.
              */
            virtual void integratorInitialized(IAPIIntegratorEvent *) = 0;
            /**
              * The listener method called just prior to the integrator step.
              * @param event Information relating to integrator event.
              */
            virtual void integratorStepStarted(IAPIIntegratorEvent *) = 0;
            /**
              * The listener method called directly after the integrator step.
              * @param event Information relating to integrator event.
              */
            virtual void integratorStepFinished(IAPIIntegratorEvent *) = 0;

    };
}
#endif
