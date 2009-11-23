/*
 *  LammpsSimulation.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATION_WRAPPER_H
#define LAMMPS_SIMULATION_WRAPPER_H

#include <vector>
#include <iostream>

#include "lammps.h"

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIRandom.h"
#include "IAPISimulation.h"
#include "IAPISimulationEventManager.h"
#include "IAPIPotentialMaster.h"
#include "LammpsBox.h"
#include "LammpsSpace.h"
#include "LammpsSpeciesManager.h"

#include "IDManager.h"

using namespace LAMMPS_NS;
using namespace molesimAPI;


namespace lammpswrappers
{

    class LammpsNeighborList;
    class LammpsRegion;;

    class LammpsSimulation : public virtual IAPISimulation {

        public:
            LammpsSimulation(int D);
            ~LammpsSimulation();

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
            void setUnitStyle(char *unitStyle);
            void setAtomStyle(char *style);
            double getTemp();
            double getKE();
            double getPE();
            double getTotalEnergy();
            LammpsSpace *getSpace();
            void addRegionWithAtoms(LammpsRegion *region);
            void setIntegrator(IAPIIntegrator *integrator);

            LAMMPS *getLammpsSim() { return mLammpsSim; }
            void setState(int state);
            int getState();
            IDManager *getMoleculeIDMgr();
            IDManager *getFixIDMgr();
            IDManager *getRegionIDMgr();
            void lammpsSetup();

            static const int UNINITIALIZED;
            static const int CREATING_ATOMS;
            static const int INITIALIZED;

        protected:
            LAMMPS *mLammpsSim;
            std::vector<IAPIBox *> mBox;
            IAPISimulationEventManager *mEventManager;
            LammpsSpeciesManager *mSpeciesManager;

        private:
            void init();
            void initThermo();
            IAPIRandom *mRand;
            int initialized;
            IDManager *moleculeIDManager;
            IDManager *fixIDManager;
            IDManager *regionIDManager;
            bool thermoInit;
            LammpsSpace *mSpace;
            IAPIIntegrator *mIntegrator;
            std::vector<LammpsRegion *>atomRegionList;
    };
}

#endif
