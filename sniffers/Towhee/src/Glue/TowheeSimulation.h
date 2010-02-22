/*
 *  TowheeSimulationSniffer.h
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
#include "TowheeSpace.h"
#include "TowheeSpeciesManager.h"
#include "IndexManager.h"

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
            IndexManager *getAtomIDMgr() { return atomIDMgr; };
            double getTemp();
            void setIntegrator(IAPIIntegrator *integrator);
            double getTotalEnergy(IAPIBox *box);

        protected:
            IAPISimulationEventManager *mEventMgr;
            TowheeSpeciesManager *mSpeciesMgr;
            TowheeSpace *mSpace;
            std::vector<IAPIBox *>mBox;
            IndexManager *atomIDMgr;

        private:
            IAPIIntegrator *mIntegrator;
    };
}

#endif
