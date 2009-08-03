/*
 *  IAPISimulation.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATION_WRAPPER_H
#define API_ISIMULATION_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIRandom.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpeciesManager.h"

namespace molesimAPI
{

    class IAPISimulation {

        public:

            virtual void addBox(IAPIBox *) = 0;
            virtual void removeBox(IAPIBox *) = 0;
            virtual int getBoxCount() = 0;
            virtual IAPIBox *getBox(int) = 0;
            virtual IAPIRandom *getRandom() = 0;
            virtual IAPISimulationEventManager *getEventManager() = 0;
            virtual IAPISpeciesManager *getSpeciesManager() = 0;
            virtual bool isDynamic() = 0;
    };
}

#endif
