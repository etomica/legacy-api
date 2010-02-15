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
#include "domain.h"
#include "library.h"
#include "output.h"
#include "compute.h"
#include "thermo.h"
#include "modify.h"
#include "compute_temp.h"

#include "LammpsSimulation.h"
#include "LammpsSimulationEventManager.h"
#include "LammpsBox.h"
#include "LammpsRandom.h"
#include "LammpsBoundaryPeriodic.h"
#include "LammpsBoundaryFixed.h"
#include "LammpsBoundaryShrink.h"
#include "LammpsBoundaryShrinkMin.h"
#include "LammpsInitialization.h"
#include "LammpsIntegrator.h"


namespace lammpssnifferwrappers
{

    LammpsSimulation::LammpsSimulation(int D, char *inputFile) {

        // Fix ID Manager
        fixIDManager = new IDManager("fix");

        // Create space
        mSpace = new LammpsSpace(D);

        // Create random number generator
        int randSeed = 0;
        while(randSeed <= 0 || randSeed >= 900000000) {
            randSeed = rand();
        }
        mRand = new LammpsRandom(this, randSeed);

        // Create species manager
        mSpeciesManager = new LammpsSpeciesManager();

        // Create event manager
        mEventManager = new LammpsSimulationEventManager();

        char **args = (char **) malloc (1*sizeof(char *));
        args[0] = (char *) malloc (50*sizeof(char));
        strcpy(args[0], "API_SIM");
        args[1] = (char *) malloc (50*sizeof(char));
        strcpy(args[1], "-screen");
        args[2] = (char *) malloc (50*sizeof(char));
        strcpy(args[2], "none");
        lammps_open(3, args, 0, (void **)&mLammpsSim);
        lammps_file(mLammpsSim, inputFile);
    }

    LammpsSimulation::~LammpsSimulation() {
        lammps_close(mLammpsSim);
    }

    /*
     * addBox()
     */

    void LammpsSimulation::addBox(IAPIBox *box) {
        printf("ERROR : LammpsSimulation::addBox(IAPIBox *) is not implemented.\n");
    }

    /*
     * removeBox()
     */
    void LammpsSimulation::removeBox(IAPIBox *box) {
        printf("ERROR : LammpsSimulation::removeBox(IAPIBox *) is not implemented.\n");
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
        printf("ERROR : LammpsSimulation::addSpecies(IAPISpecies *) is not implemented.\n");
    }

    /*
     * removeSpecies()
     *
     */
    void LammpsSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        printf("ERROR : LammpsSimulation::removeSpecies(IAPISpecies *) is not implemented.\n");
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
     * getFixIDMgr()
     */
    IDManager *LammpsSimulation::getFixIDMgr() {
        return fixIDManager;
    }

    /*
     * sniff()
     */
    void LammpsSimulation::sniff() {

        // Create boundary
        IAPIBoundary *boundary = createBoundary();

        // Create integrator
        mIntegrator = new LammpsIntegrator(this);

        // Create atom types
        LammpsInitialization *init = new LammpsInitialization(this);
        init->init();

        // Add species to species manager
        std::vector<LammpsSpecies *> sList = init->getSpecies();
        for(int i = 0; i < sList.size(); i++) {
            mSpeciesManager->addSpecies(sList[i]);
        }

        // Create box
        IAPIBox *box = NULL;

        box = new LammpsBox(this, boundary, init->getSpecies(), init->getMolecules());

        if(mBox.size() == 0) {
            mBox.push_back(box);
            mSpeciesManager->boxAddedNotify(box);
            box->setIndex(mBox.size()-1);
        }

        if(strcmp(mLammpsSim->atom->atom_style, "angle")     == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "bond")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "full")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "molecular") == 0) {
        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
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

    /*
     * createBoundary()
     */
    IAPIBoundary *LammpsSimulation::createBoundary() {

        // Create boundary
        /* From lammps source file domain.cpp :
             if (c == 'p') boundary[idim][iside] = 0;
             else if (c == 'f') boundary[idim][iside] = 1;
             else if (c == 's') boundary[idim][iside] = 2;
             else if (c == 'm') boundary[idim][iside] = 3;
             else error->all("Illegal boundary command");
        */
        int boundaryType;
        const int PERIODIC = 0;
        const int NON_PERIODIC_FIXED = 1;
        const int NON_PERIODIC_SHRINK = 2;
        const int NON_PERIODIC_SHRINK_MIN = 3;
        const int CUSTOM = 4;
        for(int i = 0; i < mSpace->getD(); i++) {
            if(mLammpsSim->domain->boundary[i][0] !=
               mLammpsSim->domain->boundary[i][1]) {
                boundaryType = CUSTOM;
                break;
            }
            if(i > 0 &&
               mLammpsSim->domain->boundary[i][0] !=
               mLammpsSim->domain->boundary[i-1][0]) {
                boundaryType = CUSTOM;
                break;
            }
            boundaryType = mLammpsSim->domain->boundary[i][0];
        }

        IAPIBoundary *boundary = NULL;

        if(boundaryType == PERIODIC) {
            boundary = new LammpsBoundaryPeriodic(this);
        }
        else if(boundaryType == NON_PERIODIC_FIXED) {
            boundary = new LammpsBoundaryFixed(this);
        }
        else if(boundaryType == NON_PERIODIC_SHRINK) {
            boundary = new LammpsBoundaryShrink(this);
        }
        else if(boundaryType == NON_PERIODIC_SHRINK_MIN) {
            boundary = new LammpsBoundaryShrinkMin(this);
        }
        else if(boundaryType == CUSTOM) {
            printf("ERROR : custom boundary type not implemented yet.\n");
        }

        return boundary;
    }

}

