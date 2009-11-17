/*
 *  TowheeSimulationSniffer.cpp
 *  API Glue
 *
 */

#include "stdlib.h"

#include "preproc.h"

#include "TowheeSimulationSniffer.h"
#include "TowheeBox.h"
#include "TowheeBoundaryRectangularPeriodic.h"
#include "TowheeMolecule.h"
#include "TowheeSpeciesManager.h"
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
extern "C" { void twh_io_directory_(int *, char *); }
extern "C" { void twh_initialize_(int *); }
extern "C" { void twh_temperature_(int *, double *); }


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
        twh_io_directory_(&set, baseDir);
        set_towhee_input_file(inputFile);
        twh_readinput_(&lfinish, &atomCount);
        sniff();
    }

    /*
     * addBox()
     */
    void TowheeSimulationSniffer::addBox(IAPIBox *box) {
        mBox.push_back(box);
    }

    /*
     * removeBox()
     */
    void TowheeSimulationSniffer::removeBox(IAPIBox *box) {
        printf("TowheeSimulationSniffer::removeBox() -> Cannot remove a box.\n"); fflush(stdout);
    }

    /*
     * getRandom()
     */
    IAPIRandom *TowheeSimulationSniffer::getRandom() {
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *TowheeSimulationSniffer::getEventManager() {
        return mEventMgr;
    }

    /*
     * getSpeciesManager()
     */
    IAPISpeciesManager *TowheeSimulationSniffer::getSpeciesManager() {
        return mSpeciesMgr;
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
     * isDynamic()
     */
    bool TowheeSimulationSniffer::isDynamic() {
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
printf("SPECIES COUNT : %d\n", getSpeciesManager()->getSpeciesCount()); fflush(stdout);
printf("BOX COUNT     : %d\n", getBoxCount()); fflush(stdout);
        for(int i = 0; i < getSpeciesManager()->getSpeciesCount(); i++) {
            IAPISpecies *species = getSpeciesManager()->getSpecies(i);
            for(int j = 0; j < getBoxCount(); j++) {
                IAPIBox *box = getBox(j);
                for(int k = 0; k < box->getNMolecules(species); k++)  {
                     IAPIMolecule *mole =
                         dynamic_cast<TowheeSpeciesSpheresMono *>(species)->makeMolecule(k);
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
        int x;
        twh_nmolty_(&get, &x);
        for(int i = 1; i <= x; i++) {
            // Number of atoms in a molecule of the species
            int y;
            twh_nunit_(&get, &i, &y);
            for(int j = 1; j <= y; j++) {
                int at;
                twh_ntype_(&get, &i, &j, &at);
//printf("%d  %d  ATOM TYPE : %d\n", i, j, at); fflush(stdout);

                bool inList = false;
                for(int idx = 0; idx < uniqueIndices; idx++) {
                    if(atomTypeIndex[idx] == at) {
                        inList = true;
//printf("  already in list...\n"); fflush(stdout);
                        break;
                    }
                }
                if(inList == false) {
//printf("  adding to list...\n"); fflush(stdout);
                    uniqueIndices++;
                    atomTypeIndex = (int *)realloc(atomTypeIndex, (uniqueIndices * sizeof(int)));
                    atomTypeIndex[uniqueIndices-1] = at;
//printf("  ... done\n"); fflush(stdout);
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
            if(numAtoms == 1) {
                int typeIndex;
                int one = 1;
                twh_ntype_(&get, &i, &one, &typeIndex);
                atomType[typeIndex-1]->setDiameter(1.5);
                species = new TowheeSpeciesSpheresMono(this, atomType[typeIndex-1]);
                atomType[typeIndex-1]->setSpecies(species);
                species->setIndex(i-1);
            }
            else {
printf("MULTI-ATOMIC SPECIES DOES NOT EXIST YET.\n"); fflush(stdout);
//                species->setIndex(i-1);
            }

            getSpeciesManager()->addSpecies(species);

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
printf("NUMBER OF BOXES : %d\n", boxCount); fflush(stdout);
        for(int i = 0; i < boxCount; i++) {
            IAPIBox *box = new TowheeBox();
            addBox(box);
            box->setIndex(i);
        }

        // Get each box boundary (assuming rectangular and periodic)
        double value[mSpace->getD()];
        for(int i = 1; i <= boxCount; i++) {
            IAPIBoundary *boundary = new TowheeBoundaryRectangularPeriodic(mSpace);
            IAPIBox *box = getBox(i-1);
            boundary->setBox(box);

printf("GETTING BOUNDARY\n"); fflush(stdout);
            for(int j = 1; j <= mSpace->getD(); j++) {
                twh_hmatrix_(&get, &i, &j, &j, &value[j-1]);
printf("  %f\n", value[j-1]); fflush(stdout);
            }

// This is not making values stored in towhee mutable,
// which is the way the vector should really operate
            IAPIVectorMutable *v = mSpace->makeVector();
printf("VECTOR : %x\n", v); fflush(stdout);

            for(int j = 0; j < mSpace->getD(); j++) {
                v->setX(j, value[j]);
            }

            boundary->setBoxSize(v);

            box->setBoundary(boundary);
        }

    }

}
