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
            virtual void integratorInitialized(IAPIIntegratorEvent *) = 0;		
            virtual void integratorStepStarted(IAPIIntegratorEvent *) = 0;		
            virtual void integratorStepFinished(IAPIIntegratorEvent *) = 0;

    };
}
#endif
