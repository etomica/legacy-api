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
#include "IAPISpecies.h"
#include "IAPIPotentialMaster.h"
#include "TowheePotentialMaster.h"
#include "TowheeSpeciesManager.h"
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
            int getBoxCount();
            IAPIBox *getBox(int index);
            void addSpecies(IAPISpecies *species);
            void removeSpecies(IAPISpecies *removedSpecies);
            int getSpeciesCount();
            IAPISpecies *getSpecies(int index);
            IAPIIntegrator *getIntegrator();

            // Non-API methods
            void setup(TowheePotentialMaster *pm, IAPIVector *config);
            static int getState();
            IndexManager *getAtomIDMgr();
            IndexManager *getMoleculeIDMgr();
            void resetCOM();
            double getTemp();
            double getTotalEnergy(IAPIBox *box);
            void setIntegrator(IAPIIntegrator *integrator);

            static const int UNINITIALIZED;
            static const int INITIALIZED;

        private:
            IAPIRandom *mRand;
            TowheeSpeciesManager *mSpeciesManager;
            IAPISimulationEventManager *mEventManager;
            IAPIIntegrator *mIntegrator;
            std::vector<IAPIBox *>mBox;
            static int mState;
            IndexManager *mAtomIDMgr;
            IndexManager *mMoleIDMgr;

    };
}

#endif
