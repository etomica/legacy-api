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
#include "IAPISpeciesManager.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeSpace.h"
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
            IAPISpeciesManager *getSpeciesManager();
            IAPIBox *getBox(int index);
            int getBoxCount();
            bool isDynamic();

            // Non-API methods
            IndexManager *getAtomIDMgr() { return atomIDMgr; };
            void sniff();
            double getTemp();

        private:
            void sniffBoxes();
            void sniffSpecies(TowheeAtomTypeSphere **atomType);
            int sniffAtomTypes();

            IAPISpeciesManager *mSpeciesMgr;
            IAPISimulationEventManager *mEventMgr;
            IndexManager *atomIDMgr;
            TowheeSpace *mSpace;
            int numBoxes;
            std::vector<IAPIBox *>mBox;
    };
}

#endif
