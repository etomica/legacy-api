/*
 *  TowheeSimulationSniffer.cpp
 *  API Glue
 *
 */

#include "stdlib.h"
#include <typeinfo>

#include "preproc.h"

#include "TowheeSimulationSniffer.h"
#include "TowheeBox.h"
#include "TowheeBoundaryRectangularPeriodic.h"
#include "TowheeIntegrator.h"
#include "TowheeMolecule.h"
#include "TowheeSpeciesManager.h"
#include "TowheeSpeciesSpheresHetero.h"
#include "TowheeSpeciesSpheresMono.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeSimulationEventManager.h"


extern "C" { void twh_readinput_(int *, int *); }
extern "C" { void twh_nmolty_(int *, int *); }
extern "C" { void twh_nunit_(int *, int *, int *); }
extern "C" { void twh_ntype_(int *, int *, int *, int *); }
//extern "C" { void twh_nmolectyp_(int *, int *, int *); }
//extern "C" { void twh_nchain_(int *, int *); }
//extern "C" { void twh_allocate_maxchain_(int *); }
extern "C" { void twh_numboxes_(int *, int *); }
//extern "C" { void twh_allocate_numboxes_(int *); }
//extern "C" { void twh_stepstyle_(int *, char *); }
//extern "C" { void twh_nstep_(int *, int *); }
//extern "C" { void twh_controlstyle_(int *, char *); }
//extern "C" { void twh_scalecut_(int *, double *); }
//extern "C" { void twh_scalelolog_(int *, double *); }
//extern "C" { void twh_scalehilog_(int *, double *); }
//extern "C" { void twh_vequiv_(int *, double *); }
//extern "C" { void twh_linit_(int *, logical *); }
//extern "C" { void twh_initboxtype_(int *, char *); }
//extern "C" { void twh_initstyle_(int *, int *, int *, char *); }
//extern "C" { void twh_initlattice_(int *, int *, int *, char *); }
//extern "C" { void twh_initmol_(int *, int *, int *, int *); }
extern "C" { void twh_hmatrix_(int *, int *, int *, int *, double *); }
extern "C" { void set_towhee_input_file(char *); }
extern "C" { void twh_io_directory_c_(int *, char *, int *); }
extern "C" { void twh_initialize_(int *); }
extern "C" { void twh_temperature_(int *, double *); }
extern "C" { void twh_boxvclassic_(int *, int *, double *); }


namespace towheesnifferwrappers
{

    TowheeSimulationSniffer::TowheeSimulationSniffer(char *inputFile) {

        numBoxes = 0;
        char blankString = '\0';
        int set = GLB_SET;
        char baseDir[6] = "/tmp/";

        int lfinish = 0;
        int atomCount;
        twh_initialize_(&lfinish);
printf("lfinish : %d\n", lfinish); fflush(stdout);
printf("BASE DIRECTORY : %s\n", baseDir);
        int len = strlen(baseDir);
        twh_io_directory_c_(&set, baseDir, &len);
        set_towhee_input_file(inputFile);
printf("INPUT FILE : %s\n", inputFile); fflush(stdout);
        twh_readinput_(&lfinish, &atomCount);
printf("lfinish : %d\n", lfinish); fflush(stdout);
        sniff();

        mIntegrator = new TowheeIntegrator();
    }

    /*
     * addBox()
     */
    void TowheeSimulationSniffer::addBox(IAPIBox *box) {
        printf("ERROR : TowheeSimulationSniffer::addBox(IAPIBox *) is not implemented.\n");
    }

    /*
     * removeBox()
     */
    void TowheeSimulationSniffer::removeBox(IAPIBox *box) {
        printf("ERROR : TowheeSimulationSniffer::removeBox() is not implemented.\n"); fflush(stdout);
    }

    /*
     * getRandom()
     */
    IAPIRandom *TowheeSimulationSniffer::getRandom() {
        printf("WARNING : TowheeSimulationSniffer::getRandom() is not implemented.\n");
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *TowheeSimulationSniffer::getEventManager() {
        return mEventMgr;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeSimulationSniffer::getBox(int index) {
        return mBox.at(index);
    }

    /*
     * getBoxCount()
     */
    int TowheeSimulationSniffer::getBoxCount() {
        return mBox.size();
    }

    /*
     * addSpecies()
     */
    void TowheeSimulationSniffer::addSpecies(IAPISpecies *species) {
        printf("TowheeSimulationSniffer::addSpecies(IAPISpecies *) is implemented but should not be.\n");
        mSpeciesMgr->addSpecies(species);
    }

    /*
     * removeSpecies()
     */
    void TowheeSimulationSniffer::removeSpecies(IAPISpecies *removedSpecies) {
        printf("TowheeSimulationSniffer::removeSpecies(IAPISpecies *) is implemented but should not be.\n");
        mSpeciesMgr->removeSpecies(removedSpecies);
    }

    /*
     * getSpeciesCount()
     */
    int TowheeSimulationSniffer::getSpeciesCount() {
        return mSpeciesMgr->getSpeciesCount();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSimulationSniffer::getSpecies(int index) {
        return mSpeciesMgr->getSpecies(index);
    }

    /*
     * getIntegrator()
     */
    IAPIIntegrator *TowheeSimulationSniffer::getIntegrator() {
        return mIntegrator;
    }

    /*
     * setIntegrator()
     */
    void TowheeSimulationSniffer::setIntegrator(IAPIIntegrator *integrator) {
        printf("ERROR : TowheeSimulationSniffer::setIntegrator(IAPIIntegrator *) is not implemented.\n");
    }

    /*
     * getTemp()
     */
    double TowheeSimulationSniffer::getTemp() {
        double temp;
        int get = GLB_GET;

        twh_temperature_(&get, &temp);

        return temp;
    }

    /*
     * getgetTotalEnergy()
     */
    double TowheeSimulationSniffer::getTotalEnergy(IAPIBox *box) {
        double energy;
        int ibox = box->getIndex() + 1;
        int get = GLB_GET;

        twh_boxvclassic_(&get, &ibox, &energy);

        return energy;

    }

    /*
     * sniff()
     */
    void TowheeSimulationSniffer::sniff() {

        mEventMgr = new TowheeSimulationEventManager();
        mSpeciesMgr = new TowheeSpeciesManager();
        mSpace = new TowheeSpace(3);
        atomIDMgr = new IndexManager(1);

        int get = GLB_GET;

printf("WARNING : ALL ATOM TYPES ARE OF TowheeAtomTypeSphere\n"); fflush(stdout);

        int atomTypeCount = sniffAtomTypes();
        TowheeAtomTypeSphere *atomType[atomTypeCount];

        for(int i = 0; i < atomTypeCount; i++) {
            atomType[i] = new TowheeAtomTypeSphere(i);
        }

        sniffSpecies(atomType);

        sniffBoxes();

        // Create the molecules by species
printf("SPECIES COUNT : %d\n", getSpeciesCount()); fflush(stdout);
printf("BOX COUNT     : %d\n", getBoxCount()); fflush(stdout);
        for(int i = 0; i < getSpeciesCount(); i++) {
            IAPISpecies *species = getSpecies(i);
            for(int j = 0; j < getBoxCount(); j++) {
                IAPIBox *box = getBox(j);
//printf("  number of molecules : %d\n", box->getNMolecules(species)); fflush(stdout);

                for(int k = 0; k < box->getNMolecules(species); k++)  {
                     IAPIMolecule *mole;
                     if(typeid(*species) == typeid(TowheeSpeciesSpheresMono)) {
//printf("    mono species\n"); fflush(stdout);
                         mole =
                             dynamic_cast<TowheeSpeciesSpheresMono *>(species)->makeMolecule();
                     }
                     else if(typeid(*species) == typeid(TowheeSpeciesSpheresHetero)) {
//printf("    hetero species\n"); fflush(stdout);
                         mole =
                             dynamic_cast<TowheeSpeciesSpheresHetero *>(species)->makeMolecule();
                     }

                     box->addMolecule(mole);
                     dynamic_cast<TowheeMolecule *>(mole)->setBox(box);
                }
            }
        }
printf("COMPLETE\n"); fflush(stdout);
    }

    /*
     * sniffAtomTypes() - 
     */
    int TowheeSimulationSniffer::sniffAtomTypes() {

        int get = GLB_GET;
        int *atomTypeIndex = NULL;
        int uniqueIndices = 0;

        // Number of species
        int specieCount;
        twh_nmolty_(&get, &specieCount);
printf("specie count : %d\n", specieCount); fflush(stdout);
        for(int i = 1; i <= specieCount; i++) {
            // Number of atoms in a molecule of the species
            int numAtoms;
            twh_nunit_(&get, &i, &numAtoms);
printf("  atoms in species : %d\n", numAtoms); fflush(stdout);
            for(int j = 1; j <= numAtoms; j++) {
                int at;
                twh_ntype_(&get, &i, &j, &at);
printf("%d  %d  ATOM TYPE : %d\n", i, j, at); fflush(stdout);

                bool inList = false;
                for(int idx = 0; idx < uniqueIndices; idx++) {
                    if(atomTypeIndex[idx] == at) {
                        inList = true;
printf("  already in list...\n"); fflush(stdout);
                        break;
                    }
                }
                if(inList == false) {
printf("  adding to list...\n"); fflush(stdout);
                    uniqueIndices++;
                    atomTypeIndex = (int *)realloc(atomTypeIndex, (uniqueIndices * sizeof(int)));
                    atomTypeIndex[uniqueIndices-1] = at;
printf("  ... done\n"); fflush(stdout);
                }
            }
        }

printf("NUMBER OF UNIQUE ATOM TYPES : %d\n", uniqueIndices);
for(int idx = 0; idx < uniqueIndices; idx++) {
printf("  Index : %d\n", atomTypeIndex[idx]); fflush(stdout);
}

        return uniqueIndices;
    }

    /*
     * sniffSpecies() - 
     */
    void TowheeSimulationSniffer::sniffSpecies(TowheeAtomTypeSphere **atomType) {

        int get = GLB_GET;

        // Create species and add to species manager
        int nmolty;
        twh_nmolty_(&get, &nmolty);
printf("NUM UNIQUE MOLECULE TYPES : %d\n", nmolty);
        for(int i = 1; i <= nmolty; i++) {

            // Get number of atoms for the molecule
            int numAtoms = 0;
            twh_nunit_(&get, &i, &numAtoms);
printf("  species : %d   num atoms : %d\n", i, numAtoms); fflush(stdout);

            // Molecules of different species do not share an atom of the
            // same atom type.
//            TowheeAtomTypeSphere *atomType = new TowheeAtomTypeSphere(i);

            IAPISpecies *species;
            int typeIndex;
            if(numAtoms == 1) {
                int one = 1;
                twh_ntype_(&get, &i, &one, &typeIndex);
                atomType[typeIndex-1]->setDiameter(1.0);
                species = new TowheeSpeciesSpheresMono(this, atomType[typeIndex-1]);
                atomType[typeIndex-1]->setSpecies(species);
                species->setIndex(i-1);
            }
            else {
                species = new TowheeSpeciesSpheresHetero(this);

                // Get atom types for the molecule
                for(int j = 1; j <= numAtoms; j++) {
                    twh_ntype_(&get, &i, &j, &typeIndex);
                    atomType[typeIndex-1]->setDiameter(1.0);
                    atomType[typeIndex-1]->setSpecies(species);
                    dynamic_cast<TowheeSpeciesSpheresHetero *>(species)->addAtomType(atomType[typeIndex-1]);
printf("TYPE INDEX : %d\n", typeIndex); fflush(stdout);
                }

                species->setIndex(i-1);
            }

            addSpecies(species);

        }

/*
            // Set number of molcules per species for each box
            for(int i = 1; i <= mBox.size(); i++) {
                for(int j = 1; j <= mSpeciesManager->getSpeciesCount(); j++) {
                    int numSpecies = mBox.at(i-1)->getNMolecules(mSpeciesManager->getSpecies(j-1));
printf("SETUP : box(%d) species(%d) -> %d\n", i, j, numSpecies); fflush(stdout);
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
*/





    }

    /*
     * sniffBoxes() - Makes the API boxes and API boundaries.  The boundaries
     *                are assumed to be rectangular and periodic.
     */
    void TowheeSimulationSniffer::sniffBoxes() {

        int get = GLB_GET;

        // Get number of boxes and allocate API box objects
        int boxCount = 0;
        twh_numboxes_(&get, &boxCount);
        double value[mSpace->getD()];

        for(int i = 1; i <= boxCount; i++) {
            // Create boundary
            for(int j = 1; j <= mSpace->getD(); j++) {
                twh_hmatrix_(&get, &i, &j, &j, &value[j-1]);
            }
            IAPIVectorMutable *v = mSpace->makeVector();
            for(int j = 0; j < mSpace->getD(); j++) {
                v->setX(j, value[j]);
            }
            // assuming rectangular and periodic
            IAPIBoundary *boundary = new TowheeBoundaryRectangularPeriodic(mSpace, v);

            // Create Box
            IAPIBox *box = new TowheeBox(boundary);
            mBox.push_back(box);
            box->setIndex(i-1);

            boundary->setBox(box);
        }

    }

}
