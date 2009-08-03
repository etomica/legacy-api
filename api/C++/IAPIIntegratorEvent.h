/*
 *  IAPIIntegratorEvent.h
 *  API Glue
 *
 */

#ifndef API_IINTEGRATOREVENT_WRAPPER_H
#define API_IINTEGRATOREVENT_WRAPPER_H

namespace molesimAPI
{

    class IAPIIntegrator;

    class IAPIIntegratorEvent {

        public:			
            virtual IAPIIntegrator *getIntegrator() = 0;
    };
}
#endif
