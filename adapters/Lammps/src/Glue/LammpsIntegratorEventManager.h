/*
 *  LammpsIntegratorEventManager.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_EVENT_MANAGER_WRAPPER_H
#define LAMMPS_INTEGERATOR_EVENT_MANAGER_WRAPPER_H

#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegratorListener.h"
#include "IAPISimulation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsIntegratorEventManager : public virtual IAPIIntegratorEventManager {

        public:			
            LammpsIntegratorEventManager(IAPISimulation *sim);

            // API Compliance
            void addListener(IAPIIntegratorListener *newListener);
            void removeListener(IAPIIntegratorListener *listener);

        private:
            LammpsSimulation *mSimulation;
            std::map<IAPIIntegratorListener *, char *> mListeners;
    };
}
#endif
