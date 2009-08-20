/*
 *  TowheeSimulation.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATION_WRAPPER_H
#define TOWHEE_SIMULATION_WRAPPER_H

#include <vector>

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulation.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpeciesManager.h"
#include "IAPIPotentialMaster.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeSimulation : public virtual IAPISimulation {

        public:
            TowheeSimulation();

            // API Compliance
            void addBox(IAPIBox *);
            void removeBox(IAPIBox *);
            IAPIRandom *getRandom();
            IAPISimulationEventManager *getEventManager();
            IAPISpeciesManager *getSpeciesManager();
            int getBoxCount();
            IAPIBox *getBox(int index);
            bool isDynamic();

            // Non-API methods
            void setup();

        private:
            IAPIRandom *mRand;
            IAPISpeciesManager *mSpeciesManager;
            std::vector<IAPIBox *>mBox;
    };
}

#endif
