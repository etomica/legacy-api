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

#include "IAPIAtom.h"
#include "LammpsSimulation.h"
#include "LammpsSimulationEventManager.h"
#include "LammpsBox.h"
//#include "LammpsSpecies.h"
#include "LammpsSpeciesSpheres.h"
#include "LammpsRandom.h"
#include "LammpsAtom.h"
#include "LammpsAtomType.h"
#include "LammpsBoundaryPeriodic.h"
#include "LammpsBoundaryFixed.h"
#include "LammpsBoundaryShrink.h"
#include "LammpsBoundaryShrinkMin.h"
//#include "LammpsBoundaryCustom.h"
//#include "LammpsBoundaryDeformable.h"
//#include "LammpsPotentialMaster.h"
#include "LammpsIntegrator.h"
//#include "LammpsIntegratorRespa.h"
//#include "LammpsIntegratorVerlet.h"
#include "LammpsMolecule.h"
//#include "LammpsNeighborList.h"


namespace lammpssnifferwrappers
{

    LammpsSimulation::LammpsSimulation(int D) {

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

//        init();
        char **args = (char **) malloc (1*sizeof(char *));
        args[0] = (char *) malloc (50*sizeof(char));
        strcpy(args[0], "API_SIM");
        args[1] = (char *) malloc (50*sizeof(char));
        strcpy(args[1], "-screen");
        args[2] = (char *) malloc (50*sizeof(char));
        strcpy(args[2], "none");
//        args[3] = (char *) malloc (50*sizeof(char));
//        strcpy(args[3], "-in");
//        args[4] = (char *) malloc (50*sizeof(char));
//        strcpy(args[4], "/tmp/lammps_step1_input");
        lammps_open(3, args, 0, (void **)&mLammpsSim);
        lammps_file(mLammpsSim, "/tmp/lammps_step1_input");
    }

    LammpsSimulation::~LammpsSimulation() {
printf("WARNING : LammpsSimulation::~LammpsSimulation() is NOT implemented.\n");

        lammps_close(mLammpsSim);
    }

    /*
     * init()
     */
/*
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
*/

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
printf("ERROR : LammpsSimulation::removeBox() does NOT remove box from simulation.\n");
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
     *
     */
    void LammpsSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        printf("ERROR : LammpsSimulation::removeSpecies() Cannot remove species from simulation.\n");
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
     * getMoleculeIDMgr()
     */
/*
    IDManager *LammpsSimulation::getMoleculeIDMgr() {
        return moleculeIDManager;
    }
*/

    /*
     * getFixIDMgr()
     */
    IDManager *LammpsSimulation::getFixIDMgr() {
        return fixIDManager;
    }

    /*
     * getRegionIDMgr()
     */
/*
    IDManager *LammpsSimulation::getRegionIDMgr() {
        return regionIDManager;
    }
*/

    /*
     * sniff()
     */
    void LammpsSimulation::sniff() {


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
printf("DIM : %d  [0] = %d  [1] = %d\n", i, mLammpsSim->domain->boundary[i][0], mLammpsSim->domain->boundary[i][1]); fflush(stdout);
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

        // Create integrator
        mIntegrator = new LammpsIntegrator(this);
        /* From lammps source style.h :
             IntegrateStyle(respa,Respa)
             IntegrateStyle(verlet,Verlet)
        */

/*
        if(strcmp(mLammpsSim->update->integration_style, "respa") == 0) {
        }
        else if(strcmp(mLammpsSim->update->integration_style, "verlet") == 0) {
        }
        else {
            printf("ERROR : Unknown integration style.\n");
        }
*/

        // Create atom types
        LammpsAtomType *atomType[mLammpsSim->atom->ntypes];
printf("DEBUG : atom types -> %d\n", mLammpsSim->atom->ntypes);
        for(int i = 0; i < mLammpsSim->atom->ntypes; i++) {
printf("  mass -> %f\n", mLammpsSim->atom->mass[i+1]);
            atomType[i]= new LammpsAtomType(i, mLammpsSim->atom->mass[i+1]);
        }

        // Create box
        IAPIBox *box = NULL;

        box = new LammpsBox(this);

        box->setBoundary(boundary);

        addBox(box);

        // Create species
        if(strcmp(mLammpsSim->atom->atom_style, "angle")     == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "bond")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "full")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "molecular") == 0) {

            // Monatomic species
            int monatomicSpeciesIdx[mLammpsSim->atom->ntypes];  // allocation overkill
            int monatomicSpeciesCount[mLammpsSim->atom->ntypes];  // allocation overkill
            int speciesCount = 0;
            for(int i = 0; i < mLammpsSim->atom->ntypes; i++) {
                monatomicSpeciesIdx[i] = 0;
                monatomicSpeciesCount[i] = 0;
            }

//            for(int i = 1; i <= (long)mLammpsSim->atom->natoms; i++) {
            for(int i = 0; i < (long)mLammpsSim->atom->natoms; i++) {
                if(mLammpsSim->atom->molecule[i] == 0) {
                    bool speciesFound = false;
                    for(int j = 0; j < speciesCount; j++) {
                        if(mLammpsSim->atom->type[i] == monatomicSpeciesIdx[j]) {
                            speciesFound = true;
                            break;
                        }
                    }
                    if(speciesFound) {
                        monatomicSpeciesCount[speciesCount-1]++;
                    }
                    else {
                        LammpsSpeciesSpheres *species = new LammpsSpeciesSpheres(this);
                        species->addChildType(atomType[mLammpsSim->atom->type[i]-1], 1);
printf("DEBUG : New species -> %d\n", mLammpsSim->atom->type[i]); fflush(stdout);
                        addSpecies(species);
                        box->addSpeciesNotify(species);
                        monatomicSpeciesIdx[speciesCount] = mLammpsSim->atom->type[i];
                        monatomicSpeciesCount[speciesCount]++;
                        speciesCount++;
                    }
                }
            }

            for(int i = 0; i < getSpeciesCount(); i++) {
printf("DEBUG : species %d    count : %d\n", monatomicSpeciesIdx[i], monatomicSpeciesCount[i]); fflush(stdout);
                box->setNMolecules(getSpecies(i), monatomicSpeciesCount[i]);
            }

        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
        }


/*
        // Create atoms
printf("DEBUG : # atoms -> %d\n", (long)mLammpsSim->atom->natoms);
LammpsAtom *atoms[long(mLammpsSim->atom->natoms)];
        for(int i = 0; i < (long)mLammpsSim->atom->natoms; i++) {
printf("  new atom type -> %d\n", mLammpsSim->atom->type[i]);
printf("  new atom tag -> %d\n", mLammpsSim->atom->tag[i]);
            atoms[i] = new LammpsAtom(this, atomType[mLammpsSim->atom->type[i]-1], mLammpsSim->atom->tag[i]-1);
        }
*/
/*
        // Create molecules and species (not sure yet how to do this...
        if(strcmp(mLammpsSim->atom->atom_style, "angle")     == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "bond")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "full")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "molecular") == 0) {

            // Monatomic molecules
            for(int i = 1; i <= (long)mLammpsSim->atom->natoms; i++) {
                if(mLammpsSim->atom->molecule[i] == 0) {
                    LammpsAtom *monatomic[1];
                    monatomic[0] = atoms[i-1];
                    // Need to make a species instead of a molecule here
                    LammpsMolecule *mole = new LammpsMolecule(monatomic, 1, -1);
                    box->addMolecule(mole);
                }
            }

/*
            int moleculeID[(int)mLammpsSim->atom->natoms];  // overkill here
            int moleculeCount = 0;

            bool inList = false;

            for(int i = 1; i <= (long)mLammpsSim->atom->natoms; i++) {
                for(int j = 0; j < moleculeCount-1; j++) {
                    if(mLammpsSim->atom->molecule[i] == moleculeID[j]) {
                        inList = true;;
                        break;
                    }
                }
                if(!inList && mLammpsSim->atom->molecule[i] > 0) {
                    moleculeID[moleculeCount] = mLammpsSim->atom->molecule[i];
                    moleculeCount++;
                }
            }
printf("DEBUG : molecule count -> %d\n", moleculeCount); fflush(stdout);

            for(int i = 0; i < moleculeCount; i++) {
printf("DEBUG : MoleculeID : %d\n", moleculeID[i]); fflush(stdout);
                for(int j = 1; j <= mLammpsSim->atom->natoms; j++) {
                    if(mLammpsSim->atom->molecule[j] == moleculeID[i]) {
printf("  DEBUG : atom in molecule : %d\n", mLammpsSim->atom->tag[j]); fflush(stdout);
                    }
                }

//                molecules[] = new LammpsMolecule();
            }
        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
        }
*/        
    }

    /*
     * setUnitStyle()
     */
/*
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
*/

    /*
     * setAtomStyle()
     */
/*
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
*/

    /*
     * getTemp()
     */
/*
    double LammpsSimulation::getTemp() {

      double temp;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("temp", &temp);

      return temp;
    }
*/

    /*
     * getKE()
     */
/*
    double LammpsSimulation::getKE() {

      double ke;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("ke", &ke);

      // Lammps returns a value normalized by the number of
      // atoms in the system.
      ke = ke * mLammpsSim->atom->natoms;;

      return ke;
    }
*/

    /*
     * getPE()
     */
/*
    double LammpsSimulation::getPE() {

      double pe;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("pe", &pe);

      // Lammps returns a value normalized by the number of
      // atoms in the system.
      pe = pe * mLammpsSim->atom->natoms;;

      return pe;
    }
*/

    /*
     * getTotalEnergy()
     */
/*
    double LammpsSimulation::getTotalEnergy() {

      double totalE;

      initThermo();

      mLammpsSim->output->thermo->evaluate_keyword("etotal", &totalE);
      // Lammps returns a value normalized by the number of
      // atoms in the system.
      totalE = totalE * mLammpsSim->atom->natoms;


      return totalE;
    }
*/

    /*
     * initThermo()
     */
/*
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
*/

    /*
     * getSpace()
     */
    LammpsSpace *LammpsSimulation::getSpace() {
        return mSpace;
    }

    /*
     * addRegionWithAtoms()
     */
/*
    void LammpsSimulation::addRegionWithAtoms(LammpsRegion *region) {
        atomRegionList.push_back(region);
    }
*/

}

