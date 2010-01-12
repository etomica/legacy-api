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

namespace lammpssnifferwrappers
{

    class LammpsSimulationEventManager : public virtual IAPISimulationEventManager {

        public:
            void addListener(IAPISimulationListener *listener);
            void removeListener(IAPISimulationListener *listener);


    };
}

#endif
