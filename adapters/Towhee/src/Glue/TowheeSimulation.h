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
            /**
              * Create a new simulation.  Initializes the native Towhee
              * simulation (twh_initialize).
              */
            TowheeSimulation();

            // API Compliance
            void addBox(IAPIBox *);
            /**
              * This method is not implemented.
              */
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
            /**
              * The setup method completes the initialization of the native
              * simulation required before the simulation can be run. (It
              * does most of the same work as the native simulation's
              * twh_mainloop method).
              * @param pm The simulation's potential master
              * @param config The simulation's initial matrix setup.  The
              *               vector holds the maximum number of molecules
              *               in each dimension for the initial matrix.
              */
            void setup(TowheePotentialMaster *pm, IAPIVector *config);
            /**
              * @return Returns the internal state of the simulation
              *         The possible state of the simulation is :
              *            UNINITIALIZED
              *            INITIALIZED
              */
            static int getState();
            /**
              * @return Returns the simulation's atom id manager.  The
              *         atom id manager is responsible for assigning
              *         and index to an atom.
              */
            IndexManager *getAtomIDMgr();
            /**
              * @return Returns the simulation's molecule id manager.  The
              *         molecule id manager is responsible for assigning
              *         and index to a molecule.
              */
            IndexManager *getMoleculeIDMgr();
            /**
              * The simulation's temperature is determined by calling
              * into the native simulation (twh_temperature).
              * @return Returns the simulation's temperature.
              */
            double getTemp();
            /**
              * The simulation's total enerty is determined by calling
              * into the native simulation (twh_boxvclassic).
              * @return Returns the simulation's total energy.
              */
            double getTotalEnergy(IAPIBox *box);
            /**
              * Assign an integrator to the simulation.
              * @param integrator The simulation's new integrator
              */
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
