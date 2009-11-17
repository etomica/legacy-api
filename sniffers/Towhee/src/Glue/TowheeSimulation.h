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
#include "IAPISpeciesManager.h"

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
            IAPISpeciesManager *getSpeciesManager();
            IAPIBox *getBox(int index);
            int getBoxCount();
            bool isDynamic();

            // Non-API methods
            void towheeSetup(double temperature);

        private:
            IAPISpeciesManager *mSpeciesMgr;
    };
}

#endif
