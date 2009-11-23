/*
 *  GlotzillaSimulation.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATION_WRAPPER_H
#define GLOTZ_SIMULATION_WRAPPER_H

#include <glotzmd.h>

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulation.h"
#include "IAPISimulationEventManager.h"
#include "IAPISpecies.h"

#include "GlotzillaBox.h"
#include "GlotzillaIntegrator.h"
#include "GlotzillaRandom.h"
#include "GlotzillaSpace.h"
#include "GlotzillaSpeciesManager.h"

#include <vector>

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaSimulation here.
      */
    class GlotzillaSimulation : public virtual IAPISimulation {

        public:
            /**
              * Create a new simulation.  Create a new instalce of a native
              * Glotzilla simulation (glotzmd::Simulation) that this
              * object will hold.  Creates a space of the dimension
              * specified.
              * @param dim The dimension of the simulation (2D - 2, 3D -3).
              */
            GlotzillaSimulation(int dim);
            /**
              * Create a new simulation. Holds the given Glotzilla
              * simulation (glotzmd::Simulation).
              * @param sim The native Glotzilla simulation
              * @todo This constructor should not be used.  The constructor
              *       is not functional.  It is a good idea, but some more
              *       thought needs to be put into what needs to be created
              *       when this ctor is called.
              */
            GlotzillaSimulation(glotzmd::Simulation* sim);
            ~GlotzillaSimulation();

            // API Compliance
            /**
              * Add a box to the simulation's box list.  Currently, only one
              * box should be used in a simulation.
              * @param box Box to add to simulation.
              */
            void addBox(IAPIBox *box);
            /**
              * Remove a box from the simulation.
              * @param box Box to remove from simulation.
              * @todo Do all the objects in the box need to be destroyed?
              */
            void removeBox(IAPIBox *box);
            /**
              * @return Return the simulation's random number generator.
              */
            IAPIRandom *getRandom();
            /**
              * @return Return the simulation's event manager.
              */
            IAPISimulationEventManager *getEventManager();
            /**
              * @param index Index into box list contained by simulation.
              * @return Returns the box held by the simulation from the
              *         box list at the given index.
              */
            IAPIBox *getBox(int index);
            /**
              * @return Returns the number of boxes in the simulation's box
              *         list.
              */
            int getBoxCount();
            void addSpecies(IAPISpecies *species);
            void removeSpecies(IAPISpecies *removedSpecies);
            int getSpeciesCount();
            IAPISpecies *getSpecies(int index);
            IAPIIntegrator *getIntegrator();

            // Non-API methods
           /**
             * WARNING : This method should not be called outside of the
             *           glue layer implementation.
             * @return Returns the Glotzilla native object
             *         (glotzmd::Simulation) that this instance is holding.
             */
            glotzmd::Simulation* getGlotzillaSim() { return mGlotzSim; }
            /**
              * @return Returns the potential energy of the simulation.
              */
            double getPotentialEnergy();
            /**
              * @return Returns the kinetic energy of the simulation.
              */
            double getKineticEnergy();
            /**
              * @return Returns the total energy of the simulation
              *         (kinetic energy + potential energy).
              */
            double getTotalEnergy();
            /**
              * @return Returns the space held by the simulation.
              */
            GlotzillaSpace *getSpace();
            void setIntegrator(IAPIIntegrator *integrator);

        protected:
            glotzmd::Simulation* mGlotzSim;
            std::vector<IAPIBox *> mBox;
            IAPISimulationEventManager *eventManager;

        private:
            void init();
            IAPIRandom *mRand;
            GlotzillaSpace *mSpace;
            GlotzillaSpeciesManager *mSpeciesManager;
            IAPIIntegrator *mIntegrator;
    };
}

#endif
