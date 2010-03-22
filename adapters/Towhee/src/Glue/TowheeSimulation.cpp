/*
 *  TowheeSimulation.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include "string.h"
#include "math.h"

#include "preproc.h"

#include "TowheeBox.h"
#include "TowheeSimulation.h"
#include "TowheeRandom.h"
#include "TowheeSimulationEventManager.h"
#include "TowheeSpeciesManager.h"

extern "C" { void twh_initialize_(int *); }
extern "C" { void twh_nmolty_(int *, int *); }
extern "C" { void twh_allocate_maxmolty_(int *); }
extern "C" { void twh_ensemble_(int *, int *); }
extern "C" { void twh_nmolectyp_(int *, int *, int *); }
extern "C" { void twh_nchain_(int *, int *); }
extern "C" { void twh_allocate_maxchain_(int *); }
extern "C" { void twh_numboxes_(int *, int *); }
extern "C" { void twh_allocate_numboxes_(int *); }
extern "C" { void twh_stepstyle_(int *, char *); }
extern "C" { void twh_controlstyle_(int *, char *); }
extern "C" { void twh_printfreq_(int *, int *); }
extern "C" { void twh_weight_freq_(int *, int *); }
extern "C" { void twh_c_matrix_freq_(int *, int *); }
extern "C" { void twh_tmmc_flag_(int *, int *); }
extern "C" { void twh_blocksize_(int *, int *); }
extern "C" { void twh_moviefreq_(int *, int *); }
extern "C" { void twh_backupfreq_(int *, int *); }
extern "C" { void twh_restartfreq_(int *, int *); }
extern "C" { void twh_runoutput_(int *, char *); }
extern "C" { void twh_pdb_output_freq_(int *, int *); }
extern "C" { void twh_pressurefreq_(int *, int *); }
extern "C" { void twh_trmaxdispfreq_(int *, int *); }
extern "C" { void twh_volmaxdispfreq_(int *, int *); }
extern "C" { void twh_scalecut_(int *, double *); }
extern "C" { void twh_scalelolog_(int *, double *); }
extern "C" { void twh_scalehilog_(int *, double *); }
extern "C" { void twh_temperature_(int *, double *); }
extern "C" { void twh_vequiv_(int *, double *); }
extern "C" { void twh_potentialstyle_(int *, int *); }
extern "C" { void twh_solvation_style_(int *, char *); }
extern "C" { void twh_set_isolvtype_(int *, char *, char *); }
extern "C" { void twh_isolvtype_(int *, int *); }
extern "C" { void twh_linit_(int *, int *); }
extern "C" { void twh_initboxtype_(int *, char *); }
extern "C" { void twh_initstyle_(int *, int *, int *, char *); }
extern "C" { void twh_initlattice_(int *, int *, int *, char *); }
extern "C" { void twh_initmol_(int *, int *, int *, int *); }
extern "C" { void twh_inixyz_(int *, int *, int *, int *, int *); }
extern "C" { void twh_hmatrix_(int *, int *, int *, int *, double *); }
extern "C" { void twh_nboxpair_(int *, int *); }
extern "C" { void twh_nvmove_(int *, int *); }
extern "C" { void twh_allocate_nvmove_(int *); }
extern "C" { void twh_pairbox_(int *, int *, int *, int *); }
extern "C" { void twh_nunit_(int *, int *, int *); }
extern "C" { void twh_allocate_maxunit_(int *); }
extern "C" { void twh_nmolectyp_(int *, int *, int *); }
extern "C" { void twh_allocate_coords_(int *, int *); }
extern "C" { void twh_initconf_(int *, int *); }
extern "C" { int twh_get_nboxi_(int *); }
extern "C" { void twh_chainlist_(int *, int *, int *, int *, int *); }
extern "C" { void twh_ctrmas_(int *, int *, int *, int *, int *); }
extern "C" { void twh_moltyp_(int *, int *, int *); }
extern "C" { void twh_parall_(int *, int *, int *, int *); }
extern "C" { void twh_masstotal_(int *, int *, double *); }
extern "C" { void twh_boxvclassic_(int *, int *, double *); }
extern "C" { void twh_ffnumber_(int *, int *); }
extern "C" { void twh_ff_filename_(int *, int *, char *); }

extern "C" { void twh_pmrotate_(int *, double *); }

namespace towheewrappers
{

    const int TowheeSimulation::UNINITIALIZED = 0;
    const int TowheeSimulation::INITIALIZED = 1;

    int TowheeSimulation::mState = TowheeSimulation::UNINITIALIZED;

    TowheeSimulation::TowheeSimulation() {

        int set = GLB_SET;

        // Create the random number generator
        mRand = new TowheeRandom(true);
//        mRand = new TowheeRandom(false);
        mSpeciesManager = new TowheeSpeciesManager();
        mEventManager = new TowheeSimulationEventManager();
        mAtomIDMgr = new IndexManager(1);
        mMoleIDMgr = new IndexManager(1);

        int lfailure;
        twh_initialize_(&lfailure);


    }

    /*
     * addBox()
     */
    void TowheeSimulation::addBox(IAPIBox *box) {
        if(mState == UNINITIALIZED) {
            mBox.push_back(box);
            mSpeciesManager->boxAddedNotify(box);
        }
        else {
printf("Cannot add a box after the simulation is initialized.\n"); fflush(stdout);
        }
    }

    /*
     * removeBox()
     */
    void TowheeSimulation::removeBox(IAPIBox *box) {
printf("WARNING : TowheeSimulation::removeBox() is NOT implemented.\n");
    }

    /*
     * getRandom()
     */
    IAPIRandom *TowheeSimulation::getRandom() {
        return mRand;
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *TowheeSimulation::getEventManager() {
        return mEventManager;
    }

    /*
     * getBoxCount()
     */
    int TowheeSimulation::getBoxCount() {
        return mBox.size();
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeSimulation::getBox(int index) {
        return mBox.at(index);
    }

    /*
     * addSpecies()
     */
    void TowheeSimulation::addSpecies(IAPISpecies *species) {
        mSpeciesManager->addSpecies(species);
    }

    /*
     * removeSpecies()
     */
    void TowheeSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        mSpeciesManager->removeSpecies(removedSpecies);
    }

    /*
     * getSpeciesCount()
     */
    int TowheeSimulation::getSpeciesCount() {
        return mSpeciesManager->getSpeciesCount();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSimulation::getSpecies(int index) {
        return mSpeciesManager->getSpecies(index);
    }

    /*
     * getIntegrator()
     */
    IAPIIntegrator *TowheeSimulation::getIntegrator() {
        return mIntegrator;
    }

    /*
     * setIntegrator()
     */
    void TowheeSimulation::setIntegrator(IAPIIntegrator *integrator) {
        mIntegrator = integrator;
    }

    /*
     * setup()
     */
    void TowheeSimulation::setup(TowheePotentialMaster *pm, IAPIVector *config) {

        int set = GLB_SET;
        int get = GLB_GET;
        int zero = 0;

        int ensemble;
        twh_ensemble_(&get, &ensemble);

        // Set number of molecule types (species)
        int speciesCount = mSpeciesManager->getSpeciesCount();
        if(speciesCount > NTMAX) {
            printf("The number of species (%d) in the simulation exceeds the maximum allowed value (%d)\n",
                   speciesCount, NTMAX);
            printf("You are doomed, my friend! (or change NTMAX in preproc.h and recompile towhee)\n");
            fflush(stdout);
        }
        twh_nmolty_(&set, &speciesCount);
        twh_allocate_maxmolty_(&speciesCount);

        // Set the number of molecules for each species
        int nchain = 0;
        for(int i = 1; i <= speciesCount; i++) {
            int moleculeCount = 0;
            IAPISpecies *species = mSpeciesManager->getSpecies(i-1);
            for(int j = 0; j < mBox.size(); j++) {
                moleculeCount += mBox.at(j)->getNMolecules(species);
            }
            twh_nmolectyp_(&set, &i, &moleculeCount);
            nchain += moleculeCount;
        }

        // Set the total number of molecules
        twh_nchain_(&set, &nchain);
        int maxChain = nchain + 1;
        twh_allocate_maxchain_(&maxChain);

        if(nchain >= NMAX) {
            printf("The number of molecules (%d) in the simulation equals or exceeds the maximum allowed value (%d)\n",
                   nchain, NMAX);
            printf("You are doomed, my friend! (or change NMAX in preproc.h and recompile towhee)\n");
            fflush(stdout);
        }

        // Set the number of boxes
        int numBoxes = mBox.size();
        twh_numboxes_(&set, &numBoxes);
        twh_allocate_numboxes_(&numBoxes);
        for(int i = 0; i < numBoxes; i++) {
            mBox.at(i)->setIndex(i);
        }
        if(numBoxes > MAXBOX) {
            printf("The number of boxes (%d) in the simulation exceeds the maximum allowed value (%d)\n",
                   numBoxes, MAXBOX);
            printf("You are doomed, my friend! (or change MAXBOX in preproc.h and recompile towhee)\n");
            fflush(stdout);
        }

        // Set step style
//        char *stepStyle = (char *) malloc ((strlen("moves") + 1) * sizeof(char));
//        strcpy(stepStyle, "moves");
        char stepStyle[8] = "moves";
        twh_stepstyle_(&set, stepStyle);
//        free(stepStyle);

        // Set control style
//        char *controlStyle = (char *) malloc ((strlen("manual") + 1) * sizeof(char));
//        strcpy(controlStyle, "manual");
        char controlStyle[20] = "manual";
        twh_controlstyle_(&set, controlStyle);

        if(strcmp(controlStyle, "manual") == 0) {
            twh_printfreq_(&set, &zero);
            twh_weight_freq_(&set, &zero);
            twh_c_matrix_freq_(&set, &zero);

            int tmmcFlag;
            twh_tmmc_flag_(&get, &tmmcFlag);
            if(tmmcFlag) {
printf("ERROR : Initialization for tmmc = TRUE not implemented.\n"); fflush(stdout);
            }

            // Set blocksize (to zero).  If set to a non-zero value, some
            // error checking needs to be performed.
            twh_blocksize_(&set, &zero);

            // Set movie frequency (to zero)
            twh_moviefreq_(&set, &zero);
            // Set backup frequency (to zero)
            twh_backupfreq_(&set, &zero);
            // Set restart save frequency (to zero)
            twh_restartfreq_(&set, &zero);

            // Set run output style
//            char *runoutputStyle = (char *) malloc ((strlen("none") + 1) * sizeof(char));
//            strcpy(runoutputStyle, "none");
            char runoutputStyle[20] = "none";
            twh_runoutput_(&set, runoutputStyle);
//            free(runoutputStyle);

            // Set PDB output frequency
            twh_pdb_output_freq_(&set, &zero);

            // Set steps between pressure calculation (to zero)
            twh_pressurefreq_(&set, &zero);

            // Set the number of steps between update of translational and
            // rotational maximum displacements
            twh_trmaxdispfreq_(&set, &zero);

            // Set the number of steps between update of volume move
            // maximum displacements
            twh_volmaxdispfreq_(&set, &zero);

        }

//        free(controlStyle);

        // set up some safety features, these are now hardwired after
        // running some tests to find good values
        double scalecut = 50.0;
        twh_scalecut_(&set, &scalecut);
        double scalelolog = powl(10.0, (-scalecut));
        twh_scalelolog_(&set, &scalelolog);
        double scalehilog = powl(10.0, scalecut);
        twh_scalehilog_(&set, &scalehilog);
        double temperature = getTemp();

        double vequiv = -logl(scalelolog)*temperature;
        twh_vequiv_(&set, &vequiv);

        // Set potential style (to internal)
        int potStyle = POT_INTERNAL;
        twh_potentialstyle_(&set, &potStyle);

        if(potStyle == POT_INTERNAL) {
            printf("WARNING : initialization code for internal potential"
                   " styles not COMPLETELY implemented.\n");
            fflush(stdout);

            // Need to implement code from twh_readclassical()
            int numFiles = pm->getForceFieldCount();
            twh_ffnumber_(&set, &numFiles);

            for(int i = 1; i <= numFiles; i++) {
                twh_ff_filename_(&set, &i, pm->getForceField(i-1)->getFileName());
            }


        }
        else if(potStyle == POT_EXTERNAL) {
            printf("ERROR : initialization code for external potential styles not implemented.\n");
            fflush(stdout);
        }

        // Set the solvation style to none
//        char *solvationStyle = (char *) malloc ((strlen("none") + 1) * sizeof(char));
//        strcpy(solvationStyle, "none");
        char solvationStyle[20];
        strcpy(solvationStyle, "none");
        twh_solvation_style_(&set, solvationStyle);
//        int failFlag;
//        char *solvationType = (char *) malloc ((strlen("") + 1) * sizeof(char));
//        strcpy(solvationType, "");
//        char solvationType[20];
//        twh_set_isolvtype_(&failFlag, solvationStyle, solvationType);
//        free(solvationStyle);
//        free(solvationType);

        int solvType = SOLV_NONE;
        twh_isolvtype_(&set, &solvType);

        if(solvType == SOLV_SASA) {
            printf("ERROR : initialization code for solvation style not implemented.\n");
            fflush(stdout);
        }
        else if(solvType == SOLV_EEF1) {
            printf("ERROR : initialization code for solvation style not implemented.\n");
            fflush(stdout);
        }
        else if(solvType == SOLV_TRAMONTO) {
            printf("ERROR : initialization code for solvation style not implemented.\n");
            fflush(stdout);
        }

        if(solvType != SOLV_NONE) {
            printf("ERROR : error checking code for solvation style not implemented.\n");
            fflush(stdout);
        }

        // Set linit (to true)
        int linit = 1;
        twh_linit_(&set, &linit);

        // Set initboxtype (to dimensions)
//        char *initBoxType = (char *) malloc ((strlen("dimensions") + 1) * sizeof(char));
//        strcpy(initBoxType, "dimensions");
        char initBoxType[20] = "dimensions";
        twh_initboxtype_(&set, initBoxType);

        if(strcmp(initBoxType, "unit cell") == 0) {
            printf("ERROR : initialization code for initboxtype of 'unit cell' not implemented.\n");
            fflush(stdout);
        }

        if(strcmp(initBoxType, "dimensions") == 0 ||
           strcmp(initBoxType, "number density") == 0) {

            // Set init style (to full cbmc)
//            char *initStyle = (char *) malloc ((strlen("full cbmc") + 1) * sizeof(char));
//            strcpy(initStyle, "full cbmc");
            char initStyle[20] = "full cbmc";
            for(int i = 1; i <= mBox.size(); i++) {
                for(int j = 1; j <= mSpeciesManager->getSpeciesCount(); j++) {
                    twh_initstyle_(&set, &i, &j, initStyle);
                } // species loop
            } // box loop

            // Additional information required if init style is 'helix cbmc'
            // This initialization is not coded.

            // Set init lattice (to 'simple cubic')
//            char *initLattice = (char *) malloc ((strlen("simple cubic") + 1) * sizeof(char));
//            strcpy(initLattice, "simple cubic");
            char initLattice[20] = "simple cubic";
            for(int i = 1; i <= mBox.size(); i++) {
                for(int j = 1; j <= mSpeciesManager->getSpeciesCount(); j++) {
                    twh_initlattice_(&set, &i, &j, initLattice);
                } // species loop
            } // box loop

            // Set number of molcules per species for each box
            for(int i = 1; i <= mBox.size(); i++) {
                for(int j = 1; j <= mSpeciesManager->getSpeciesCount(); j++) {
                    int numSpecies = mBox.at(i-1)->getNMolecules(mSpeciesManager->getSpecies(j-1));
                    twh_initmol_(&set, &i, &j, &numSpecies);

                    IAPIMoleculeList *moleList = mBox.at(i-1)->getMoleculeList(mSpeciesManager->getSpecies(j-1));

                    int numAtoms = moleList->getMolecule(0)->getChildList()->getAtomCount();

                    // Set number of atoms for the molecule
                    twh_nunit_(&set, &j, &numAtoms);

                    // Set the mass for the molecule (sum of its atom's mass)
                    for(int k = 0; k < moleList->getMoleculeCount(); k++) {
                        double mass = 0.0;
                        int idx = moleList->getMolecule(k)->getIndex() + 1;
                        for(int l = 0;
                            l < moleList->getMolecule(k)->getChildList()->getAtomCount();
                            l++) {
                            mass += moleList->getMolecule(k)->getChildList()->getAtom(l)->getType()->getMass();
                        }
                        twh_masstotal_(&set, &idx, &mass);
                    }

                } // species loop
            } // box loop

        }

        printf("ERROR : inix, iniy, iniz initialization not completed.\n"); fflush(stdout);
        for(int i = 1; i <= mBox.size(); i++) {
            int inix = config->getX(0);
            int iniy = config->getX(1);
            int iniz = config->getX(2);
            twh_inixyz_(&set, &i, &inix, &iniy, &iniz);
        }

        if(strcmp(initBoxType, "dimensions") == 0) {
printf("WARNING : setting hmatrix using hardcoded space dimension(3).\n"); fflush(stdout);
            for(int ibox = 1; ibox <= mBox.size(); ibox++) {
                IAPIBoundary *boundary = mBox.at(ibox-1)->getBoundary();
                double boundaryDim;
                for(int i = 1; i <= 3; i++) {
                    for(int j = 1; j <= 3; j++) {
                        if(i == j) boundaryDim = boundary->getBoxSize()->getX(j-1);
                        else boundaryDim = 0.0;
                        twh_hmatrix_(&set, &ibox, &i, &j, &boundaryDim);
                    }
                }
            }
        }
        else if(strcmp(initBoxType, "number density") == 0) {
            printf("ERROR : initialization code for initBoxType 'number density' not implemented.\n");
            fflush(stdout);
        }

//        free(initBoxType);

        // determine the number of possible box pairs
        int boxPairs = numBoxes*(numBoxes-1)/2;
        twh_nboxpair_(&set, &boxPairs);
        if(ensemble == ENS_NPT) twh_nvmove_(&set, &numBoxes);
        else twh_nvmove_(&set, &boxPairs);

        int numMoves;
        twh_nvmove_(&get, &numMoves);
        twh_allocate_nvmove_(&numMoves);

        // set up pairbox array (used for volume and swap moves)
        int itest = 0;
        int one = 1;
        int two = 2;
        for(int ibox = 1; ibox <= numBoxes-1; ibox++) {
            for(int jbox = ibox+1; jbox <= numBoxes; jbox++) {
                itest++;
                twh_pairbox_(&set, &itest, &one, &ibox);
                twh_pairbox_(&set, &itest, &two, &jbox);
            }
        }

        if((ensemble == ENS_NVT && numBoxes > 1) ||
           (ensemble == ENS_NPT)) {
            printf("ERROR : pmvol initialization not implemented.\n");
            fflush(stdout);
        }

        if((ensemble == ENS_NVT && numBoxes > 1) ||
           (ensemble == ENS_NPT)) {
            printf("ERROR : pmcell initialization not implemented.\n");
            fflush(stdout);
        }

        if(numBoxes > 1) {
            printf("ERROR : initialization for simulation with more than one box not implemented.\n");
            fflush(stdout);
        }

        if(ensemble == ENS_UVT) {
            printf("ERROR : initialization for  grand canonical insertion/deletion for UVT ensemble not implemented.\n");
            fflush(stdout);
        }

printf("ERROR : initialization for  MOVE STUFF not implemented.\n");
fflush(stdout);

printf("ERROR : initialization for  POTENTIALS not implemented.\n");
fflush(stdout);


        // set pmrotate to 1.0
//       double onePointZero = 1.0;
//       twh_pmrotate_(&set, &onePointZero);



        // finished reading input from towhee_input
        // determine the largest value of nunit
        int maxunit = 0;
        int numunits;
        for(int i = 1; i <= speciesCount; i++) {
            twh_nunit_(&get, &i, &numunits);
            if (numunits > maxunit) maxunit = numunits;
        }
//printf("maxunit : %d\n", maxunit); fflush(stdout);
        // allocate arrays based maxunit
        twh_allocate_maxunit_(&maxunit);

        // compute the total number of atoms
        int natoms = 0;
        int numMoles;
        for(int i = 1; i <= speciesCount; i++) {
            twh_nmolectyp_(&get, &i, &numMoles);
//printf("numMoles : %d\n", numMoles); fflush(stdout);
            twh_nunit_(&get, &i, &numunits);
//printf("  numunits : %d\n", numunits); fflush(stdout);
            natoms +=  numMoles * numunits;
//printf("    natoms : %d\n", natoms); fflush(stdout);
        }

//printf("natoms : %d  maxunit : %d\n", natoms, maxunit); fflush(stdout);
        // allocate arrays for coords
        twh_allocate_coords_(&natoms, &maxunit);

        // SKIPPED STUFF IN readtowhee.F

        // get or generate the initial configuration of the system
        if (linit) {
            int confFail;
            int atomCount;
            twh_initconf_(&confFail, &atomCount);
        }
        else {
            printf("Cannot read initial configuration from file.\n"); fflush(stdout);
        }

        int moleType;
        int *counter = (int *) calloc (speciesCount, sizeof(int));
        for(int ibox = 1; ibox <= getBoxCount(); ibox++) {

            for(int i = 1; i <= nchain; i++) {
                if(twh_get_nboxi_(&i) == ibox) {
                    twh_moltyp_(&get, &i, &moleType);
                }
                counter[moleType]++;
                twh_chainlist_(&set, &counter[moleType], &i, &moleType, &i);
            }
        }
        free(counter);

        counter = (int *) calloc (speciesCount, sizeof(int));

        for(int i = 1; i <= nchain; i++) {
            twh_moltyp_(&get, &i, &moleType);
            counter[moleType]++;
            twh_parall_(&set, &moleType, &counter[moleType], &i);
        }
        free(counter);

        int ctrInitial = CTR_INITIAL;
        int failFlag;
        for(int ibox = 1; ibox <= getBoxCount(); ibox++) {
            twh_ctrmas_(&failFlag, &zero, &ibox, &zero, &ctrInitial);
        }

        mState = INITIALIZED;
    }

    /*
     * getState()
     */
    int TowheeSimulation::getState() {
        return mState;
    }

    /*
     * getAtomIDMgr()
     */
    IndexManager *TowheeSimulation::getAtomIDMgr() {
        return mAtomIDMgr;
    }

    /*
     * getMoleculeIDMgr()
     */
    IndexManager *TowheeSimulation::getMoleculeIDMgr() {
        return mMoleIDMgr;
    }

    /*
     * getTemp()
     */
    double TowheeSimulation::getTemp() {
        double temp;
        int get = GLB_GET;

        twh_temperature_(&get, &temp);

        return temp;
    }

    /*
     * getTotalEnergy()
     */
    double TowheeSimulation::getTotalEnergy(IAPIBox *box) {
        double energy;
        int ibox = box->getIndex() + 1;
        int get = GLB_GET;

        twh_boxvclassic_(&get, &ibox, &energy);

        return energy;
    }

}

