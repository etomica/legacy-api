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
#include "IAPISpeciesManager.h"
#include "IAPIPotentialMaster.h"
#include "LammpsBox.h"
#include "LammpsSpace.h"

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
            IAPISpeciesManager *getSpeciesManager();
            int getBoxCount();
            IAPIBox *getBox(int index);
            bool isDynamic();

            // Non-API methods
            void setUnitStyle(char *unitStyle);
            void setAtomStyle(char *style);
            double getTemp();
            double getKE();
            double getPE();
            double getTotalEnergy();
            LammpsSpace *getSpace();
            void addRegionWithAtoms(LammpsRegion *region);

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
            IAPISpeciesManager *mSpeciesManager;

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
            std::vector<LammpsRegion *>atomRegionList;
    };
}

#endif
