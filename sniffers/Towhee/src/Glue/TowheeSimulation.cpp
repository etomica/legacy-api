/*
 *  TowheeSimulation.cpp
 *  API Glue
 *
 */

#include <complex>

#include "preproc.h"

#include "IAPIMoleculeList.h"
#include "IAPIVector.h"
#include "TowheeSimulation.h"
#include "TowheeSpeciesManager.h"

extern "C" { void twh_nmolty_(int *, int *); } // Number of molecule types in system
extern "C" { void twh_nmolectyp_(int *, int *, int *); } // Number of molecule in system
                                                         // for the given molecule type
extern "C" { void twh_nchain_(int *, int *); } // Number of molecules in system
extern "C" { void twh_allocate_maxchain_(int *); }
extern "C" { void twh_numboxes_(int *, int *); } // Number of boxes in system
extern "C" { void twh_allocate_numboxes_(int *); }
extern "C" { void twh_stepstyle_(int *, char *); }
extern "C" { void twh_nstep_(int *, int *); }
extern "C" { void twh_controlstyle_(int *, char *); }
extern "C" { void twh_scalecut_(int *, double *); }
extern "C" { void twh_scalelolog_(int *, double *); }
extern "C" { void twh_scalehilog_(int *, double *); }
extern "C" { void twh_vequiv_(int *, double *); }
//extern "C" { void twh_linit_(int *, logical *); }
extern "C" { void twh_initboxtype_(int *, char *); }
extern "C" { void twh_initstyle_(int *, int *, int *, char *); }
extern "C" { void twh_initlattice_(int *, int *, int *, char *); }
extern "C" { void twh_initmol_(int *, int *, int *, int *); }
extern "C" { void twh_hmatrix_(int *, int *, int *, int *, double *); }
extern "C" { void twh_nunit_(int *, int *, int *); } // Number of atoms for the given molecule


namespace towheesnifferwrappers
{

    TowheeSimulation::TowheeSimulation() {
        mSpeciesMgr = new TowheeSpeciesManager();
    }

    /*
     * addBox()
     */
    void TowheeSimulation::addBox(IAPIBox *box) {
    }

    /*
     * removeBox()
     */
    void TowheeSimulation::removeBox(IAPIBox *box) {
    }

    /*
     * getRandom()
     */
    IAPIRandom *TowheeSimulation::getRandom() {
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *TowheeSimulation::getEventManager() {
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeSimulation::getBox(int index) {
    }

    /*
     * getBoxCount()
     */
    int TowheeSimulation::getBoxCount() {
    }

    /*
     * addSpecies()
     */
    void TowheeSimulation::addSpecies(IAPISpecies *species) {
        mSpeciesMgr->addSpecies(species);
    }

    /*
     * removeSpecies()
     */
    void TowheeSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        mSpeciesMgr->removeSpecies(removedSpecies);
    }

    /*
     * getSpeciesCount()
     */
    int TowheeSimulation::getSpeciesCount() {
        return mSpeciesMgr->getSpeciesCount();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeSimulation::getSpecies(int index) {
        return mSpeciesMgr->getSpecies(index);
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
     * towheeSetup()
     */
    void TowheeSimulation::towheeSetup(double temperature) {

        int set = GLB_SET;

        // Need to set the number of molecule types
        // Is this the number of unique species?
        int nmolty = getSpeciesCount();
        twh_nmolty_(&set, &nmolty);

        // The total number of molecules in the system
        int numMolecules = 0;
        for(int i = 0; i < nmolty; i++) {
            int idx = i + 1;
            // The total number of molecules for the looped species
            int moleCount = 0;
            for(int j = 0; j < getBoxCount(); j++) {
                moleCount += getBox(j)->getMoleculeList(
                             getSpecies(i))->getMoleculeCount();
                numMolecules += moleCount;
            }
            // Set the number of molecules for the looped species
            twh_nmolectyp_(&set, &idx, &moleCount);
        }

        // Set the total number of molecules in the system
        twh_nchain_(&set, &numMolecules);

        int maxChain = numMolecules + 1;
        twh_allocate_maxchain_(&maxChain);

        // Number of boxes in system
        int boxCount = getBoxCount();
        twh_numboxes_(&set, &boxCount);

        int maxBoxCount = boxCount + 1;
        twh_allocate_numboxes_(&maxBoxCount);

        // Set the step style and number of steps
        char stepStyle[16] = "moves";
        twh_stepstyle_(&set, stepStyle);

        int numSteps = 1;
        twh_nstep_(&set, &numSteps);

        // Set Control style
//        char controlStyle[32] = "";
//        twh_controlstyle_(&set, controlStyle);

        // From Towhee :
        // --- set up some safety features, these are now hardwired after
        // --- running some tests to find good values
        double scalecut = 50.0;
        twh_scalecut_(&set, &scalecut);

        double scalelolog = pow(10.0, (-scalecut));
        twh_scalelolog_(&set, &scalelolog);

        double scalehilog = pow(10.0, (scalecut));
        twh_scalehilog_(&set, &scalehilog);

        double vequiv = -log((scalelolog)*temperature);
        twh_vequiv_(&set, &vequiv);

        // Set linit to true (I think)
        // Actually, may not need to set this.  May just need
        // to do setup where the flag is checked
//        twh_linit_(&set, XXXX);

        // Set initial box type
        char initBoxType[32] = "dimensions";
        twh_initboxtype_(&set, initBoxType);

// NOT SURE the initstyle SETTING IS CORRECT
        for(int i = 0; i < getBoxCount(); i++) {
            int idx = i + 1;
            char initStyle[32] = "coords";
            for(int j = 0; j < nmolty; j++) {
                int idx2 = j+1;
                twh_initstyle_(&set, &idx, &idx2, initStyle);
            }
        }

// NOT SURE the initlattice setting is correct
        for(int i = 0; i < getBoxCount(); i++) {
            int idx = i + 1;
            for(int j = 0; j < nmolty; j++) {
                int idx2 = j+1;
                char initLattice[32] = "none";
                twh_initlattice_(&set, &idx, &idx2, initLattice);
            }
        }

// NOTE : THIS IS NOT WORKING IF A SPECIES IS IN SOME BOXES, BUT NOT
//        OTHERS
        // Set number of molecules in each box
        for(int i = 0; i < getBoxCount(); i++) {
            int idx = i + 1;
            for(int j = 0; j < nmolty; j++) {
                int idx2 = j+1;
                int moleCount = getBox(i)->getNMolecules(getSpecies(j));
                twh_initmol_(&set, &idx, &idx2, &moleCount);
            }
        }

// inix, iniy, iniz must be specified here

        // set up box boundary
        for(int i = 0; i < getBoxCount(); i++) {
            int idx = i + 1;
            IAPIVector *v = getBox(i)->getBoundary()->getBoxSize();
            for(int j = 1; j <=3; j++) {
                for(int k = 1; k <=3; k++) {
                    double value;
                    i == k ? v->getX(k) : 0.0;
                    twh_hmatrix_(&set, &idx, &j, &k, &value);
                }
            }
        }

// LEFT OFF AT LINE 1174 of readtowhee.F

    }

}
