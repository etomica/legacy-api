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
            /**
              * @return Returns the boundary associated with the boundary
              *         event.
              */
            virtual IAPIBoundary *getBoundary() = 0;
    };
}
#endif
