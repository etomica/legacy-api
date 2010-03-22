/*
 *  IAPIBoundaryEventManager.h
 *  API Glue
 *
 */

#ifndef API_IBOUNDARYEVENTMGR_WRAPPER_H
#define API_IBOUNDARYEVENTMGR_WRAPPER_H

#include "IAPIBoundaryListener.h"

namespace molesimAPI
{

    /**
      * IAPIBoundaryEventManager fires boundary events to any listeners
      * registered to receive boundary events.  A listener is notified of any
      * boundary event whether the listener is interested in the event or not.
      * If the listener is not interested in the event, it can ignore the event.
      */
    class IAPIBoundaryEventManager {

        public:
            /**
              * Register a boundary listener to receive boundary events.
              * @param listener Boundary listener to receive events.
              */
            virtual void addListener(IAPIBoundaryListener *listener) = 0;
            /**
              * Unregister a boundary listener from receiving boundary events.
              * @param listener Boundary listener to unregister.
              */
            virtual void removeListener(IAPIBoundaryListener *listener) = 0;

    };
}
#endif
