/*
 *  TowheeBoundaryEventManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOUNDARYEVENTMGR_WRAPPER_H
#define TOWHEE_BOUNDARYEVENTMGR_WRAPPER_H

#include "IAPIBoundaryEventManager.h"
#include "IAPIBoundaryListener.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeBoundaryEventManager fires boundary events to any listeners
      * registered to receive boundary events.  A listener is notified of any
      * boundary event whether the listener is interested in the event or not.
      * If the listener is not interested in the event, it can ignore the event.
      * The listener determines the kind of event by checking the type of
      * the event class.
      */
    class TowheeBoundaryEventManager : public virtual IAPIBoundaryEventManager {

        public:
            /**
              * Register a boundary listener to receive boundary events.
              * @param listener Boundary listener to receive events.
              */
            void addListener(IAPIBoundaryListener *listener);
            /**
              * Unregister a boundary listener from receiving boundary events.
              * @param listener Boundary listener to unregister.
              */
            void removeListener(IAPIBoundaryListener *listener);

    };
}

#endif
