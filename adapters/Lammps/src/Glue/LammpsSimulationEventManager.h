/*
 *  LammpsSimulationEventManager.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONEVTMGR_WRAPPER_H
#define LAMMPS_SIMULATIONEVTMGR_WRAPPER_H

#include "IAPISimulationEventManager.h"
#include "IAPISimulationListener.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * NOTE : The class is not implemented.
      * LammpsSimulationEventManager fires simulation events to any
      * listeners registered to receive simulation events.  A listener is
      * notified of any simulation event whether the listener is interested
      * in the event or not.  If the listener is not interested in the event,
      * it can ignore the event.
      */
    class LammpsSimulationEventManager : public virtual IAPISimulationEventManager {

        public:
            /**
              * This method is not implemented.
              */
            void addListener(IAPISimulationListener *listener);
            /**
              * This method is not implemented.
              */
            void removeListener(IAPISimulationListener *listener);

        protected:

    };
}

#endif
