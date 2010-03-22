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

    /**
      * @todo Description of GlotzillaSimulation here.
      */
    class IAPISimulation {

        public:

            /**
              * Add a box to the simulation's box list.
              * @param box Box to add to simulation.
              */
            virtual void addBox(IAPIBox *) = 0;
            /**
              * Remove a box from the simulation.
              * @param box Box to remove from simulation.
              */
            virtual void removeBox(IAPIBox *) = 0;
            /**
              * @return Returns the number of boxes in the simulation's box
              *         list.
              */
            virtual int getBoxCount() = 0;
            /**
              * @param index Index into box list contained by simulation.
              * @return Returns the box held by the simulation from the
              *         box list at the given index.
              */
            virtual IAPIBox *getBox(int) = 0;
            /**
              * Add a new species to the simulation.
              * @param species Species to add to the simulation.
              */
            virtual void addSpecies(IAPISpecies *species) = 0;
            /**
              * Remove a species from the simulation.
              * @param species removedSpecies to add to the simulation.
              */
            virtual void removeSpecies(IAPISpecies *removedSpecies) = 0;
            /**
              * @return Returns the number of unique species in the
              *         simulation.
              */
            virtual int getSpeciesCount() = 0;
            /**
              * @param index Index into the simulation's species list.
              * @return Returns the species, at the given index, from the
              *         simulation's species list.
              */
            virtual IAPISpecies *getSpecies(int index) = 0;
            /**
              * @return Returns the simulation's integrator.
              */
            virtual IAPIIntegrator *getIntegrator() = 0;
            /**
              * @return Return the simulation's random number generator.
              */
            virtual IAPIRandom *getRandom() = 0;
            /**
              * @return Return the simulation's event manager.
              */
            virtual IAPISimulationEventManager *getEventManager() = 0;
    };
}

#endif
