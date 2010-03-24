/*
 *  IAPISimulationEventManager.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONEVENTMGR_WRAPPER_H
#define API_ISIMULATIONEVENTMGR_WRAPPER_H

#include "IAPISimulationListener.h"

namespace molesimAPI
{

    /**
      * IAPISimulationEventManager fires simulation events to any
      * listeners registered to receive simulation events.  A listener is
      * notified of any simulation event whether the listener is interested
      * in the event or not.  If the listener is not interested in the event,
      * it can ignore the event.
      */
    class IAPISimulationEventManager {

        public:
            /**
              * Add an event listener to the event manager.
              * @param listener The listener to notify when an event occurs.
              */
            virtual void addListener(IAPISimulationListener *) = 0;
            /**
              * Remove an event listener from the event manager.
              * @param listener The listener to remove.
              */
            virtual void removeListener(IAPISimulationListener *) = 0;

    };
}
#endif
