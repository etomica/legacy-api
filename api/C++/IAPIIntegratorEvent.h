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
            /**
              * @return Returns the integrator related to the event.
              */
            virtual IAPIIntegrator *getIntegrator() = 0;
    };
}
#endif
