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
            virtual void doStep() = 0;		
            virtual long long getStepCount() = 0;		
            virtual void reset() = 0;
            virtual void resetStepCount() = 0;
            virtual IAPIIntegratorEventManager *getEventManager() = 0;

    };
}
#endif
