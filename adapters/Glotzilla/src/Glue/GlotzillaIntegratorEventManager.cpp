/*
 *  GlotzillaIntegratorEventManager.cpp
 *  API Glue
 *
 */

#include "GlotzillaIntegratorEventManager.h"
#include "GlotzillaSimulation.h"

namespace glotzwrappers
{

    GlotzillaIntegratorEventManager::GlotzillaIntegratorEventManager(IAPISimulation *sim) {
        mSim = sim;
    }
	
    /*
     * addListener
     */
    void GlotzillaIntegratorEventManager::addListener(IAPIIntegratorListener *newListener) {
        if(mListeners.count(newListener) == 0) {
            GlotzillaIntegratorListener *listen =
                new GlotzillaIntegratorListener(newListener);
            mListeners.insert(std::pair<IAPIIntegratorListener *, GlotzillaIntegratorListener *>
               (newListener, listen));
            dynamic_cast<GlotzillaSimulation *>(mSim)->getGlotzillaSim()->
                AddSimulationModifier(listen);
        }
        else {
            printf("WARNING : Listener already held by the integrator.\n");
            fflush(stdout);
        }
    }

    /*
     * removeListener
     */
    void GlotzillaIntegratorEventManager::removeListener(IAPIIntegratorListener *listener) {
        if(mListeners.count(listener) == 0) {
            dynamic_cast<GlotzillaSimulation *>(mSim)->getGlotzillaSim()->
                RemoveSimulationModifier(mListeners[listener]);
            mListeners.erase(listener);
        }
    }

}
