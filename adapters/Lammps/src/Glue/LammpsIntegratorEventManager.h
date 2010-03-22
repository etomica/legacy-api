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
            /**
              * Adds a listener that will be notified of integrator events.
              * Native Lammps calls :
              *    fix
              *
              * @param newListener The listener to be notified of the
              *                    integrator events.
              */
            void addListener(IAPIIntegratorListener *newListener);
            /**
              * Removes a listener that was being notified of integrator
              * events.
              * Native Lammps calls :
              *    unfix
              *
              * @param listener The listener to be removed from the integrator
              *                 event notifications.
              */
            void removeListener(IAPIIntegratorListener *listener);

        private:
            LammpsSimulation *mSimulation;
            std::map<IAPIIntegratorListener *, char *> mListeners;
    };
}
#endif
