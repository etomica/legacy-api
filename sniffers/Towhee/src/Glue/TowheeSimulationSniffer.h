/*
 *  TowheeSimulationSniffer.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATION_SNIFFER_WRAPPER_H
#define TOWHEE_SIMULATION_SNIFFER_WRAPPER_H

#include <vector>

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulation.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpecies.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeSpace.h"
#include "TowheeSpeciesManager.h"
#include "IndexManager.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeSimulationSniffer : public virtual IAPISimulation {

        public:

            TowheeSimulationSniffer(char *inputFile);

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
            void sniff();
            double getTemp();
            void setIntegrator(IAPIIntegrator *integrator);

        private:
            void sniffBoxes();
            void sniffSpecies(TowheeAtomTypeSphere **atomType);
            int sniffAtomTypes();

            TowheeSpeciesManager *mSpeciesMgr;
            IAPISimulationEventManager *mEventMgr;
            IndexManager *atomIDMgr;
            TowheeSpace *mSpace;
            IAPIIntegrator *mIntegrator;
            int numBoxes;
            std::vector<IAPIBox *>mBox;
    };
}

#endif
