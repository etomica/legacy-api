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
            /**
              * Create a new simulation.  Creates a space of the dimension
              * specified.  Opens an instance of the native Lammps
              * simulation (lammps_open).  Issues the dimension command
              * to the native Lammps simulation.  Initializes the atom style
              * to bond.
              * Native Lammps calls :
              *   lammps_open
              *   dimension
              * @param D The dimension of the simulation (2D - 2, 3D -3).
              */
            LammpsSimulation(int D);
            ~LammpsSimulation();

            // API Compliance
            /**
              * Add a box to the simulation's box list.  Only one box can
              * be added to the simulation at this time.
              * @param box Box to add to simulation.
              */
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
            /**
              * Set the native Lammps simulation unit style.
              * @param unitStyle The string containing the simulation's
              *                  unit style.  For more information on the
              *                  unit style, see the native Lammps command
              *                  documentation.
              * Native Lammps calls :
              *   units
              */
            void setUnitStyle(char *unitStyle);
            /**
              * Set the native Lammps simulation atom style.
              * @param style The string containing the simulation's
              *              atom style.  For more information on the
              *              atom style, see the native Lammps command
              *              documentation.
              * Native Lammps calls :
              *   atom_style
              */
            void setAtomStyle(char *style);
            /**
              * The simulation's temperature is determined by reaching
              * into the native simulation.
              * @return Returns the simulation's temperature.
              */
            double getTemp();
            /**
              * The simulation's kinetic energy is determined by reaching
              * into the native simulation.
              * @return Returns the kinetic energy of the simulation.
              */
            double getKE();
            /**
              * The simulation's potential energy is determined by reaching
              * into the native simulation.
              * @return Returns the potential energy of the simulation.
              */
            double getPE();
            /**
              * The simulation's total energy is determined by reaching
              * into the native simulation.
              * @return Returns the total energy of the simulation.
              */
            double getTotalEnergy();
            /**
              * @return Returns the space held by the simulation.
              */
            LammpsSpace *getSpace();
            /**
              * Remove a box from the simulation.
              * @param box Box to remove from simulation.
              */
            void setIntegrator(IAPIIntegrator *integrator);

            /**
              * @return Returns a native Lammps Simlation object pointer.
              */
            LAMMPS *getLammpsSim() { return mLammpsSim; }
            /**
              * Sets the simulation's internal state to one of the
              * following :
              *            UNINITIALIZED
              *            CREATING_ATOMS
              *            INITIALIZED
              * @param state New simulation state
              */
            void setState(int state);
            /**
              * @return Returns the internal state of the simulation
              *         The possible state of the simulation is :
              *            UNINITIALIZED
              *            CREATING_ATOMS
              *            INITIALIZED
              */
            int getState();
            /**
              * @return Returns the simulation's molecule id manager.  The
              *         molecule id manager is responsible for assigning
              *         and index to a molecule.
              */
            IDManager *getMoleculeIDMgr();
            /**
              * @return Returns the simulation's fix id manager.  The
              *         fix id manager is responsible for assigning
              *         a unique index for a new fix.  A fix is a component
              *         in a native Lammps simulation and requires a unique
              *         identifier.
              */
            IDManager *getFixIDMgr();
            /**
              * @return Returns the simulation's region id manager.  The
              *         region id manager is responsible for assigning
              *         a unique index for a new region.  A region is a
              *         component in a native Lammps simulation and requires
              *         a unique identifier.
              */
            IDManager *getRegionIDMgr();
           /**
              * Enforce a 2D simulation (if 2D) and set the native lammps
              * thermo style.
              * Native Lammps calls :
              *    fix
              *    thermo_style
              */
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
