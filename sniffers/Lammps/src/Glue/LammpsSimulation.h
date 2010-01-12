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
#include "LammpsSpace.h"
#include "LammpsSpeciesManager.h"

#include "IDManager.h"

using namespace LAMMPS_NS;
using namespace molesimAPI;


namespace lammpssnifferwrappers
{

//    class LammpsNeighborList;
//    class LammpsRegion;;

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
            LammpsSpace *getSpace();
/*
            void setUnitStyle(char *unitStyle);
            void setAtomStyle(char *style);
            double getTemp();
            double getKE();
            double getPE();
            double getTotalEnergy();
            void addRegionWithAtoms(LammpsRegion *region);
*/

            LAMMPS *getLammpsSim() { return mLammpsSim; }
/*
            IDManager *getMoleculeIDMgr();
            IDManager *getRegionIDMgr();
*/
            IDManager *getFixIDMgr();

            void sniff();

        protected:
            LAMMPS *mLammpsSim;
            std::vector<IAPIBox *> mBox;
            LammpsSpeciesManager *mSpeciesManager;
            IAPISimulationEventManager *mEventManager;

        private:
/*
            void init();
            void initThermo();
            int initialized;
            IDManager *moleculeIDManager;
            IDManager *regionIDManager;
            bool thermoInit;
            std::vector<LammpsRegion *>atomRegionList;
*/
            IDManager *fixIDManager;
            IAPIIntegrator *mIntegrator;
            IAPIRandom *mRand;
            LammpsSpace *mSpace;
    };
}

#endif
