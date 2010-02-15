/*
 *  LammpsIntegratorEventManager.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsIntegratorEventManager.h"

namespace lammpssnifferwrappers
{

    LammpsIntegratorEventManager::LammpsIntegratorEventManager(LammpsSimulation *sim) {
        mSimulation = sim;
    }
	
    /*
     * addListener()
     */
    void LammpsIntegratorEventManager::addListener(IAPIIntegratorListener *newListener) {
        if(mListeners.count(newListener) == 0) {
            char *fixID = mSimulation->getFixIDMgr()->getNextID();
            char command[256];
            sprintf(command,
                    "fix %s all api_integrator_listener 1 %x",
                    fixID,
                    newListener);
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSimulation->getLammpsSim(), command);

            // Save the fix id
            mListeners.insert(std::pair<IAPIIntegratorListener *,
                                        char *>(newListener, fixID));
        }
        else {
            printf("WARNING : Integrator Listener already added to integrator event manager.\n");
            fflush(stdout);
        }
    }

    /*
     * removeListener()
     */
    void LammpsIntegratorEventManager::removeListener(IAPIIntegratorListener *listener) {
        if(mListeners.count(listener) == 0) {
            printf("WARNING : Integrator Listener not managed by integrator event manager.\n");
            fflush(stdout);
        }
        else {
            char command[256];
            sprintf(command,
                    "unfix %s",
                    mListeners[listener]);
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSimulation->getLammpsSim(), command);
            mListeners.erase(listener);
        }
    }
}
