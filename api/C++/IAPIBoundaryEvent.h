/*
 *  IAPIBoundaryEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOUNDARYEVENT_WRAPPER_H
#define API_IBOUNDARYEVENT_WRAPPER_H

namespace molesimAPI
{

    class IAPIBoundary;

    class IAPIBoundaryEvent {

        public:			
            virtual IAPIBoundary *getBoundary() = 0;
    };
}
#endif
