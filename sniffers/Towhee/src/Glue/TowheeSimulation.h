/*
 *  TowheeSimulation.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATION_WRAPPER_H
#define TOWHEE_SIMULATION_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulation.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpecies.h"
#include "TowheeSpeciesManager.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeSimulation : public virtual IAPISimulation {

        public:

            TowheeSimulation();

            void addBox(IAPIBox *box);
            void removeBox(IAPIBox *box);
            IAPIRandom *getRandom();
            IAPISimulationEventManager *getEventManager();
            IAPIBox *getBox(int index);
            int getBoxCount();
            void addSpecies(IAPISpecies *species);
            void removeSpecies(IAPISpecies *removedSpecies);
            int getSpeciesCount();
            IAPISpecies *getSpecies(int index);
            IAPIIntegrator *getIntegrator();

            // Non-API methods
            void towheeSetup(double temperature);
            void setIntegrator(IAPIIntegrator *integrator);

        private:
            TowheeSpeciesManager *mSpeciesMgr;
            IAPIIntegrator *mIntegrator;
    };
}

#endif
