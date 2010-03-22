/*
 *  LammpsSimulation.cpp
 *  API Glue
 *
 */
#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "atom.h"
#include "library.h"
#include "output.h"
#include "compute.h"
#include "thermo.h"
#include "modify.h"
#include "compute_temp.h"

#include "LammpsSimulation.h"
#include "LammpsSimulationEventManager.h"
#include "LammpsSpecies.h"
#include "LammpsSpeciesManager.h"
#include "LammpsSpeciesSpheres.h"
#include "LammpsRandom.h"
#include "LammpsRegion.h"
#include "LammpsBoundaryCustom.h"
#include "LammpsBoundaryDeformable.h"
#include "LammpsPotentialMaster.h"
#include "LammpsIntegrator.h"
#include "LammpsIntegratorRespa.h"
#include "LammpsIntegratorVerlet.h"
#include "LammpsNeighborList.h"


namespace lammpswrappers
{

    const int LammpsSimulation::UNINITIALIZED = 0;
    const int LammpsSimulation::CREATING_ATOMS = 1;
    const int LammpsSimulation::INITIALIZED = 2;

    LammpsSimulation::LammpsSimulation(int D) {

        mSpace = new LammpsSpace(D);

        // Create a simulation
        init();
    }

    LammpsSimulation::~LammpsSimulation() {
printf("WARNING : LammpsSimulation::~LammpsSimulation() is NOT implemented.\n");

        lammps_close(mLammpsSim);
    }

    /*
     * init()
     */
    void LammpsSimulation::init() {
        initialized = UNINITIALIZED;
        char **args = (char **) malloc (1*sizeof(char *));
        args[0] = (char *) malloc (50*sizeof(char));
        strcpy(args[0], "API_SIM");
        args[1] = (char *) malloc (50*sizeof(char));
        strcpy(args[1], "-screen");
        args[2] = (char *) malloc (50*sizeof(char));
        strcpy(args[2], "none");
        lammps_open(3, args, 0, (void **)&mLammpsSim);
        mEventManager = new LammpsSimulationEventManager();
        mSpeciesManager = new LammpsSpeciesManager();
        // Lammps random number generator needs a seed between
        // 0 and 900000000 exclusive.
        int randSeed = 0;
        while(randSeed <= 0 || randSeed >= 900000000) {
            randSeed = rand();
        }
        mRand = new LammpsRandom(this, randSeed);
        IAPIBox *box = LammpsBox::instance(this);
        addBox(box);
        moleculeIDManager = new IDManager("molecule");
        fixIDManager = new IDManager("fix");
        regionIDManager = new IDManager("region");
        thermoInit = false;

        char command[256];
//printf("lammps_command : echo none\n");
//        lammps_command(mLammpsSim, "echo none");

//printf("WARNING : Logging is turned OFF\n"); fflush(stdout);
//printf("lammps_command : log none\n");
//        lammps_command(mLammpsSim, "log none");

        sprintf(command,
                "dimension %d",
                mSpace->getD());
printf("lammps_command : %s\n", command);
        lammps_command(mLammpsSim, command);

        setAtomStyle("bond");

    }

    /*
     * addBox()
     */
    void LammpsSimulation::addBox(IAPIBox *box) {
        if(mBox.size() == 0) {
            mBox.push_back(box);
            mSpeciesManager->boxAddedNotify(box);
            box->setIndex(mBox.size()-1);
        }
        else {
            printf("The Simulation already contains a box.\n"); fflush(stdout);
        }
    }

    /*
     * removeBox()
     */
    void LammpsSimulation::removeBox(IAPIBox *box) {
printf("WARNING : LammpsSimulation::removeBox() does NOT remove box from simulation if lammps has already started.\n");

        // Remove box from list
        int index = -1;

        for(int i = 0; i < mBox.size(); i++) {
            if(mBox.at(i) == box) {
                index = i;
                break;
            }
        }

        mBox.erase(mBox.begin()+index, mBox.begin()+index+1);

    }

    /*
     * getRandom()
     */
    IAPIRandom *LammpsSimulation::getRandom() {
        return mRand;
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *LammpsSimulation::getEventManager() {
        return(mEventManager);
    }

    /*
     * getBoxCount()
     */
    int LammpsSimulation::getBoxCount() {
        return mBox.size();
    }

    /*
     * getBox()
     */
    IAPIBox *LammpsSimulation::getBox(int index) {
        return mBox.at(index);
    }

    /*
     * addSpecies()
     */
    void LammpsSimulation::addSpecies(IAPISpecies *species) {
        mSpeciesManager->addSpecies(species);
    }

    /*
     * removeSpecies()
     */
    void LammpsSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        mSpeciesManager->removeSpecies(removedSpecies);
    }

    /*
     * getSpeciesCount()
     */
    int LammpsSimulation::getSpeciesCount() {
        return mSpeciesManager->getSpeciesCount();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *LammpsSimulation::getSpecies(int index) {
        return mSpeciesManager->getSpecies(index);
    }

    /*
     * getIntegrator()
     */
    IAPIIntegrator *LammpsSimulation::getIntegrator() {
        return mIntegrator;
    }

    /*
     * setIntegrator()
     */
    void LammpsSimulation::setIntegrator(IAPIIntegrator *integrator) {
        mIntegrator = integrator;
    }

    /*
     * getState()
     */
    int LammpsSimulation::getState() {
        return initialized;
    }

    /*
     * setState()
     */
    void LammpsSimulation::setState(int state) {
        initialized = state;
    }

    /*
     * getMoleculeIDMgr()
     */
    IDManager *LammpsSimulation::getMoleculeIDMgr() {
        return moleculeIDManager;
    }

    /*
     * getFixIDMgr()
     */
    IDManager *LammpsSimulation::getFixIDMgr() {
        return fixIDManager;
    }

    /*
     * getRegionIDMgr()
     */
    IDManager *LammpsSimulation::getRegionIDMgr() {
        return regionIDManager;
    }

    /*
     * lammpsSetup()
     */
    void LammpsSimulation::lammpsSetup() {

        char command[512]; // Any command longer than 512 characters is SOL

        LammpsSpeciesManager *sm = dynamic_cast<LammpsSpeciesManager *>(mSpeciesManager);

        if(mSpace->getD() == 2) {
            sprintf(command,
                    "fix %s all enforce2d",
                    fixIDManager->getNextID());
printf("lammps_command : %s\n", command);
            lammps_command(mLammpsSim, command);
        }

// thermo_style    custom step temp epair etotal press vol
printf("TEMPORARY lammps_command : %s\n", "thermo_style    custom step temp pe ke etotal press vol"); fflush(stdout);
lammps_command(mLammpsSim, "thermo_style    custom step temp pe ke etotal press vol");

    }

    /*
     * setUnitStyle()
     */
    void LammpsSimulation::setUnitStyle(char *unitStyle) {
        if(initialized == UNINITIALIZED) {
            char command[256];
            sprintf(command, "units %s", unitStyle);
printf("lammps_command : %s\n", command);
            lammps_command(mLammpsSim, command);
        }
        else {
            printf("ERROR : The unit style cannot be set after the simulation is initialized.\n");
            fflush(stdout);
        }
    }

    /*
     * setAtomStyle()
     */
    void LammpsSimulation::setAtomStyle(char *style) {
        if(initialized == UNINITIALIZED) {
            char command[512];
            sprintf(command, "atom_style %s", style);
printf("lammps_command : %s\n", command);
            lammps_command(mLammpsSim, command);
        }
        else {
            printf("ERROR : The atom style cannot be set after the simulation is initialized.\n");
            fflush(stdout);
        }
    }

    /*
     * getTemp()
     */
    double LammpsSimulation::getTemp() {

      double temp;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("temp", &temp);

      return temp;
    }

    /*
     * getKE()
     */
    double LammpsSimulation::getKE() {

      double ke;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("ke", &ke);

      // Lammps returns a value normalized by the number of
      // atoms in the system.
      ke = ke * mLammpsSim->atom->natoms;;

      return ke;
    }

    /*
     * getPE()
     */
    double LammpsSimulation::getPE() {

      double pe;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("pe", &pe);

      // Lammps returns a value normalized by the number of
      // atoms in the system.
      pe = pe * mLammpsSim->atom->natoms;;

      return pe;
    }

    /*
     * getTotalEnergy()
     */
    double LammpsSimulation::getTotalEnergy() {

      double totalE;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("etotal", &totalE);
      // Lammps returns a value normalized by the number of
      // atoms in the system.
      totalE = totalE * mLammpsSim->atom->natoms;


      return totalE;
    }

    /*
     * initThermo()
     */
    void LammpsSimulation::initThermo() {
      if(!thermoInit) {
        mLammpsSim->output->thermo->init();
        Modify *modify = mLammpsSim->modify;
        for(int i = 0; i < modify->ncompute; i++) {
          if(typeid(*modify->compute[i]) == typeid(ComputeTemp)) {
            modify->compute[i]->init();
          }
        }
        thermoInit = true;
      }
    }

    /*
     * getSpace()
     */
    LammpsSpace *LammpsSimulation::getSpace() {
        return mSpace;
    }

}

