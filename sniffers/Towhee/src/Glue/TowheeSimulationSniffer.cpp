/*
 *  TowheeSimulationSniffer.cpp
 *  API Glue
 *
 */

#include "stdlib.h"
#include <typeinfo>
#include <vector>

#include "preproc.h"

#include "TowheeSimulationSniffer.h"
#include "TowheeAtom.h"
#include "TowheeBox.h"
#include "TowheeBoundaryRectangularPeriodic.h"
#include "TowheeIntegrator.h"
#include "TowheeMonatomicMolecule.h"
#include "TowheeSpeciesSpheresHetero.h"
#include "TowheeSpeciesSpheresMono.h"
#include "TowheeAtomTypeSphere.h"


extern "C" { void twh_readinput_(int *, int *); }
extern "C" { void twh_nmolty_(int *, int *); }
extern "C" { void twh_nunit_(int *, int *, int *); }
extern "C" { void twh_ntype_(int *, int *, int *, int *); }
extern "C" { void twh_numboxes_(int *, int *); }
extern "C" { void twh_hmatrix_(int *, int *, int *, int *, double *); }
extern "C" { void set_towhee_input_file(char *); }
extern "C" { void twh_io_directory_c_(int *, char *, int *); }
extern "C" { void twh_initialize_(int *); }
extern "C" { void twh_initmol_(int *, int *, int *, int *); }


namespace towheesnifferwrappers
{

    TowheeSimulationSniffer::TowheeSimulationSniffer(char *inputFile) {

        char blankString = '\0';
        int set = GLB_SET;
        char baseDir[6] = "/tmp/";

        int lfinish = 0;
        int atomCount;
        twh_initialize_(&lfinish);
        int len = strlen(baseDir);
        twh_io_directory_c_(&set, baseDir, &len);
        set_towhee_input_file(inputFile);
        twh_readinput_(&lfinish, &atomCount);
        sniff();

    }

    /*
     * sniff()
     */
    void TowheeSimulationSniffer::sniff() {

        int get = GLB_GET;

printf("WARNING : ALL ATOM TYPES ARE OF TowheeAtomTypeSphere\n"); fflush(stdout);

        int atomTypeCount = sniffAtomTypes();
        TowheeAtomTypeSphere *atomType[atomTypeCount];

        for(int i = 0; i < atomTypeCount; i++) {
            atomType[i] = new TowheeAtomTypeSphere(i);
        }

        sniffSpecies(atomType);

        sniffBoxes();

        sniffMolecules(atomType);
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
//printf("specie count : %d\n", specieCount); fflush(stdout);
        for(int i = 1; i <= specieCount; i++) {
            // Number of atoms in a molecule of the species
            int numAtoms;
            twh_nunit_(&get, &i, &numAtoms);
//printf("  atoms in species : %d\n", numAtoms); fflush(stdout);
            for(int j = 1; j <= numAtoms; j++) {
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

            mSpeciesMgr->addSpecies(species);

        }

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

    /*
     * sniffMolecules()
     */
    void TowheeSimulationSniffer::sniffMolecules(TowheeAtomTypeSphere **atomType) {

        int get = GLB_GET;

        // Create the molecules by species
        int boxCount = 0;
        twh_numboxes_(&get, &boxCount);
        int specieCount;
        twh_nmolty_(&get, &specieCount);
printf("SPECIES COUNT : %d\n", specieCount); fflush(stdout);
printf("BOX COUNT     : %d\n", boxCount); fflush(stdout);

        for(int i = 1; i <= specieCount; i++) {
            IAPISpecies *species = getSpecies(i-1);

            for(int j = 1; j <= boxCount; j++) {


                int numMolecules;
                twh_initmol_(&get, &j, &i, &numMolecules);
                for(int k = 0; k < numMolecules; k++)  {
                    int numAtoms = 0;
                    twh_nunit_(&get, &i, &numAtoms);

                    std::vector<TowheeAtom *>atoms;

                    // Make atoms with correct atom type
                    for(int atIdx = 1; atIdx <= numAtoms; atIdx++)  {
                        int atomIndex;
                        twh_ntype_(&get, &i, &atIdx, &atomIndex);

                        atoms.push_back(new TowheeAtom(atomType[atomIndex-1],
                                                       getBox(j-1),
                                                       getAtomIDMgr()->getNextIndex()));
                    }

                    // Make molecule and pass atoms into molecule ctor
                    IAPIMolecule *mole = new TowheeMonatomicMolecule(atoms, species);

                    for(int atIdx = 0; atIdx < numAtoms; atIdx++)  {
                        atoms[atIdx]->setParent(mole);
                    }

                    getBox(j-1)->addMolecule(mole);
                }
            }
        }

    }
}
