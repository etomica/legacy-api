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
        IAPIBoundary *boundary = createBoundary();

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

        int nativeAtomID[mLammpsSim->atom->ntypes];
        int count = 0;
        for(int i = 0; i < mLammpsSim->atom->natoms; i++) {
            bool inList = false;
printf("my index : %d   atom type %d\n", i, mLammpsSim->atom->type[i]);
            for(int j = 0; j < count; j++) {
                if(nativeAtomID[j] == mLammpsSim->atom->type[i]) {
                    inList = true;
                    break;
                }
            }
            if(!inList) {
                nativeAtomID[count] = mLammpsSim->atom->type[i];
                count++;
            }
        }
printf("UNIQUE ATOM IDS FOUND(WHICH SHOULD MATCH ACTUAL NATIVE ATOM TYPES) : %d\n", count);

        for(int i = 0; i < mLammpsSim->atom->ntypes; i++) {
printf("DEBUG : Creating new atom type -> %d  %d  %f\n", i, nativeAtomID[i], mLammpsSim->atom->mass[i+1]);
            atomType[i]= new LammpsAtomType(i, nativeAtomID[i], mLammpsSim->atom->mass[i+1]);
        }

        // Create box
        IAPIBox *box = NULL;

        box = new LammpsBox(this);

        box->setBoundary(boundary);

        addBox(box);


        if(strcmp(mLammpsSim->atom->atom_style, "angle")     == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "bond")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "full")      == 0 ||
           strcmp(mLammpsSim->atom->atom_style, "molecular") == 0) {

            NativeMolecule **molecules = NULL;
            int moleculeCount = 0;
printf("moleculeCount address : %x\n", &moleculeCount);

            for(int atomIdx = 0; atomIdx < (long)mLammpsSim->atom->natoms; atomIdx++) {
                // monatomic molecule may have molecule id of 0
                if(mLammpsSim->atom->molecule[atomIdx+1] == 0) {
                    // Create new NativeMolecule (create a private function in this class)
                    NativeMolecule *mole = createMoleculeData(&moleculeCount, atomIdx);
                    molecules = (NativeMolecule **) realloc (molecules, (moleculeCount) * sizeof(NativeMolecule *));
                    molecules[moleculeCount-1] = mole;
                }
                else {
                    bool inList = false;
                    for(int moleIdx = 0; moleIdx < moleculeCount; moleIdx++) {
                        if(mLammpsSim->atom->molecule[atomIdx+1] == molecules[moleIdx]->nativeID) {
                            inList = true;
                            break;
                        }
                    }
                    if(!inList) {
                        // Create new NativeMolecule (create a private function in this class)
                        NativeMolecule *mole = createMoleculeData(&moleculeCount, atomIdx);
                    }
                }                
            }
printf("DEBUG : %d MOLECULES FOUND.\n", moleculeCount); fflush(stdout);
for(int i = 0; i < moleculeCount; i++) {
printf("MOLECULE : %d  # atoms : %d  -> ", molecules[i]->nativeID, molecules[i]->atomCount);
for(int j = 0; j < molecules[i]->atomCount; j++) {
printf("  atom id : %d  ", molecules[i]->nativeAtomID[j]);
}
printf("\n");
}
fflush(stdout);
            int speciesCount = 0;

            NativeSpecies *species;
            species = createSpeciesData(molecules, moleculeCount, &speciesCount);
printf("DEBUG : %d SPECIES FOUND\n", speciesCount); fflush(stdout);
for(int i = 0; i < speciesCount; i++) {
printf("SPECIES : %d\n", i);
printf("  # molecules of species : %d\n", species[i].moleculeCount);
printf("  molecules ID : ");
for(int j = 0; j < species[i].moleculeCount; j++) {
printf("  %d", species[i].moleculeID[j]);
}
printf("\n");
printf("  # atom types : %d\n", species[i].numAtomTypes);
for(int j = 0; j < species[i].numAtomTypes; j++) {
printf("    atom type : %d\n", species[i].atomTypes[j]);
}
}
fflush(stdout);

printf("WARNING : specie child type list is not a unique list(atom types repeated if more than one atom of the type in molecule) and shoud be.\n");
            for(int specIdx = 0; specIdx < speciesCount; specIdx++) {
                LammpsSpeciesSpheres *specie = new LammpsSpeciesSpheres(this);
                for(int atIdx = 0; atIdx < species[specIdx].numAtomTypes; atIdx++) {
                    for(int i = 0; i < mLammpsSim->atom->ntypes; i++) {
                        if(species[specIdx].atomTypes[atIdx] == atomType[i]->getNativeIndex()) {
printf("Adding atom type to species idx : %d\n", specIdx);
                            specie->addChildType(atomType[i], 1);
                            break;
                        }
                    }
                }
                addSpecies(specie);
                box->addSpeciesNotify(specie);

                // Create molecules of this species and add to box
                for(int moleIdx = 0; moleIdx < moleculeCount; moleIdx++) {
//printf("molecule species : %x     species : %x\n", molecules[moleIdx]->species, &species[specIdx]);
                    if(molecules[moleIdx]->speciesIndex == specIdx) {
printf("Create molecule of species idx : %d\n", specIdx);
                        LammpsMolecule *mole = new LammpsMolecule(molecules[moleIdx]->nativeID);

                        // Create atoms for molecule
                        for(int atomIdx = 0; atomIdx < molecules[moleIdx]->atomCount; atomIdx++) {

                            LammpsAtomType *at = NULL;

                            for(int allIdx = 0; allIdx < mLammpsSim->atom->ntypes; allIdx++) {
                                if(species[specIdx].atomTypes[atomIdx] == atomType[allIdx]->getNativeIndex()) {
                                  at = atomType[atomIdx];
printf("    ATOM TYPE : %d\n", allIdx);
                                  break;
                                }
                            }

                            LammpsAtom *atom =
                              new LammpsAtom(this, at,
                                         molecules[moleIdx]->nativeAtomID[atomIdx]);
printf("    CREATE THE ATOM : %d\n", molecules[moleIdx]->nativeAtomID[atomIdx]);

                            // Add atom to molecule
                            mole->addChildAtom(atom);
                        }
                    }
                }
            }
        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
        }
/*
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
                // make molecule and have molecule hold its lammps molecule id
                // (if it has one)
                LammpsMolecule *mole = new LammpsMolecule(<MOLE ID>);
                LammpsAtom *atom = new LammpsAtom(this, getSpecies(i)->getAtomType(0), <ATOM ID>);

                // add molecule to box with addMolecule(IAPIMolecule *)
                // addMolecule(IAPIMolecule *) should also update its species list/count
                // also needs to update box's leaf list
                // set molecules index, molecules atoms' index and atoms leaf index

//                box->setNMolecules(getSpecies(i), monatomicSpeciesCount[i]);
            }

        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
        }
*/

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

    /*
     * createMoleculeData()
     */
    LammpsSimulation::NativeMolecule *LammpsSimulation::createMoleculeData(int *moleCount, int atomPos) {
        NativeMolecule *moles = NULL;

        // atomPos is the index within the atom class in lammps of the first atom
        // in the newly discovered molecule

        moles = (NativeMolecule *) malloc (sizeof(NativeMolecule));

        // Fill in new native molecule struct here
        moles->nativeID = mLammpsSim->atom->molecule[atomPos];
        moles->speciesIndex = -1;
        moles->nativeAtomID = (int *)malloc(sizeof(int));
        moles->nativeAtomID[0] = atomPos;
printf("DEBUG : NEW MOLECULE %d   first atom pos %d\n",moles->nativeID ,atomPos);
fflush(stdout);
        moles->atomCount = 1;

        // Look for rest of atoms in molecule if not monatomic
        if(moles->nativeID > 0) {
            for(int i = atomPos + 1; i <= mLammpsSim->atom->natoms; i++) {
                if(mLammpsSim->atom->molecule[i] == moles->nativeID) {
                    moles->atomCount++;
                    moles->nativeAtomID =
                       (int *)realloc(moles->nativeAtomID,
                       (moles->atomCount) * sizeof(int));
                    moles->nativeAtomID[moles->atomCount-1] = i;
printf("  Another atom form molecule %d   atom pos %d\n",moles->nativeID ,i);
fflush(stdout);
                }
            }
        }
        *moleCount = *moleCount + 1;

        return moles;
    }

    /*
     * createSpeciesData()
     */
    LammpsSimulation::NativeSpecies *LammpsSimulation::createSpeciesData(NativeMolecule **moles, int moleCount,
                                             int *speciesCount) {

        NativeSpecies *species = NULL;
for(int i = 0; i < moleCount; i++) {
printf("MOLECULE : %d  # atoms : %d  -> ", moles[i]->nativeID, moles[i]->atomCount);
for(int j = 0; j < moles[i]->atomCount; j++) {
printf("  atom id : %d  ", moles[i]->nativeAtomID[j]);
}
printf("\n");
}
fflush(stdout);

        if(moleCount == 0) {
            return NULL;
        }
printf("MOLECOUNT : %d\n", moleCount);

        for(int i = 0; i < moleCount; i++) {
            // found a molecule does not not have an associated species
            if(moles[i]->speciesIndex == -1) {
printf("DEBUG : FOUND a new species for molecule in position %d\n", i); fflush(stdout);
printf("  MOLECULE : %d  # atoms : %d  -> ", moles[i]->nativeID, moles[i]->atomCount);
for(int j = 0; j < moles[i]->atomCount; j++) {
printf("    atom id : %d  ", moles[i]->nativeAtomID[j]);
}
printf("\n");
fflush(stdout);
                species = (NativeSpecies *) realloc (species, (*speciesCount+1) * sizeof(NativeSpecies));
                moles[i]->speciesIndex = *speciesCount;
printf("  species : %x\n", species[*speciesCount]);
                species[*speciesCount].moleculeCount = 1;
                species[*speciesCount].moleculeID = (int *) malloc (sizeof(int));
                species[*speciesCount].moleculeID[0] = moles[i]->nativeID;

                species[*speciesCount].numAtomTypes = moles[i]->atomCount;
                species[*speciesCount].atomTypes = (int *) malloc
                   (species[*speciesCount].numAtomTypes * sizeof(int));
                for(int j = 0; j < moles[i]->atomCount; j++) {
                    species[*speciesCount].atomTypes[j] =
                       mLammpsSim->atom->type[moles[i]->nativeAtomID[j]];
                }

printf("  new species %d  atom type : %d\n", *speciesCount, species[*speciesCount].atomTypes[0]); fflush(stdout);

                // Look thru other molecules to see if they are of this species
                // Will only be considered same species if atom types is list
                // are in the same order
                for(int j = i+1; j < moleCount; j++) {
                    if(moles[j]->nativeID == species[*speciesCount].moleculeID[0] &&
                       moles[j]->atomCount == species[*speciesCount].numAtomTypes) {
                        for(int k = 0; k < moles[j]->atomCount; k++) {
                            if(mLammpsSim->atom->type[moles[j]->nativeAtomID[k]] ==
                               species[*speciesCount].atomTypes[k]) {
                                species[*speciesCount].moleculeID = (int *) realloc
                                   (species[*speciesCount].moleculeID,
                                   (species[*speciesCount].moleculeCount+1)* sizeof(int));
                                species[*speciesCount].moleculeID[species[*speciesCount].moleculeCount] =
                                   moles[j]->nativeID;
                                species[*speciesCount].moleculeCount++;
                                moles[j]->speciesIndex = *speciesCount;

                            }
                        }
                    }
                }

                *speciesCount = *speciesCount + 1;
            }

        }

        return species;

   
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

        return boundary;
    }

}

