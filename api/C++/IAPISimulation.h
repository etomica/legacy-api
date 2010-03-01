/*
 *  IAPISimulation.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATION_WRAPPER_H
#define API_ISIMULATION_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpecies.h"

namespace molesimAPI
{

    class IAPISimulation {

        public:

            virtual void addBox(IAPIBox *) = 0;
            virtual void removeBox(IAPIBox *) = 0;
            virtual int getBoxCount() = 0;
            virtual IAPIBox *getBox(int) = 0;
            virtual void addSpecies(IAPISpecies *species) = 0;
            virtual void removeSpecies(IAPISpecies *removedSpecies) = 0;
            virtual int getSpeciesCount() = 0;
            virtual IAPISpecies *getSpecies(int index) = 0;
            virtual IAPIIntegrator *getIntegrator() = 0;
            virtual IAPIRandom *getRandom() = 0;
            virtual IAPISimulationEventManager *getEventManager() = 0;
    };
}

#endif
