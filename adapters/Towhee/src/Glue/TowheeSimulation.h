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
#include "IndexManager.h"

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
            void setup(IAPIVector *config);
            static int getState();
            IndexManager *getAtomIDMgr();
            IndexManager *getMoleculeIDMgr();
            void resetCOM();
            double getTemp();
            double getTotalEnergy(IAPIBox *box);

            static const int UNINITIALIZED;
            static const int INITIALIZED;

        private:
            IAPIRandom *mRand;
            IAPISpeciesManager *mSpeciesManager;
            IAPISimulationEventManager *mEventManager;
            std::vector<IAPIBox *>mBox;
            static int mState;
            IndexManager *mAtomIDMgr;
            IndexManager *mMoleIDMgr;

    };
}

#endif
