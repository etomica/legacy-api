/*
 *  LammpsIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define LAMMPS_INTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include <map>

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"
#include "IAPISimulation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsIntegratorEventManager : public virtual IAPIIntegratorEventManager {

        public:			
            LammpsIntegratorEventManager(LammpsSimulation *sim);

            // API Compliance
            void addListener(IAPIIntegratorListener *newListener);
            void removeListener(IAPIIntegratorListener *listener);

        private:
            LammpsSimulation *mSimulation;
            std::map<IAPIIntegratorListener *, char *> mListeners;
    };
}
#endif
