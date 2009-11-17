/*
 *  TowheeSimulationEventManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONEVTMGR_WRAPPER_H
#define TOWHEE_SIMULATIONEVTMGR_WRAPPER_H

#include "IAPISimulationEventManager.h"
#include "IAPISimulationListener.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeSimulationEventManager fires simulation events to any
      * listeners registered to receive simulation events.  A listener is
      * notified of any simulation event whether the listener is interested
      * in the event or not.  If the listener is not interested in the event,
      * it can ignore the event.
      */
    class TowheeSimulationEventManager : public virtual IAPISimulationEventManager {

        public:
            /**
              * Add an event listener to the event manager.
              * @param listener The listener to notify when an event occurs.
              */
            void addListener(IAPISimulationListener *listener);
            /**
              * Remove an event listener from the event manager.
              * @param listener The listener to remove.
              */
            void removeListener(IAPISimulationListener *listener);

    };
}

#endif
