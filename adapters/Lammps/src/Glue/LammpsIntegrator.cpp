/*
 *  LammpsIntegrator.cpp
 *  API Glue
 *
 */

#include "lammps.h"
#include "library.h"
#include "modify.h"

#include "IAPIBox.h"
#include "LammpsIntegrator.h"
#include "LammpsSimulation.h"
#include "LammpsIntegratorEventManager.h"
#include "LammpsIntegratorVerlet.h"
#include "LammpsIntegratorRespa.h"

//
// NOTE : NPT and NVT are not working properly for different tStart and tStop
//        As the simulation is running one step at a time and the run command
//        is not making use of the ability to "stretch" the temp change out
//        over the entire run.  That is somewhat difficult as the total #
//        of steps is NOT known.  I guess lammps is somewhat predicated on
//        that advanced knowledge.
//
namespace lammpswrappers
{

    const int LammpsIntegrator::NONE = 0;
    const int LammpsIntegrator::NVE  = 1;
    const int LammpsIntegrator::NVT  = 2;
    const int LammpsIntegrator::NPT  = 3;
    const int LammpsIntegrator::NPH  = 4;

    LammpsIntegrator::LammpsIntegrator(IAPISimulation *sim) {
        mSimulation = dynamic_cast<LammpsSimulation *>(sim);
        mEventManager = (IAPIIntegratorEventManager *)(new LammpsIntegratorEventManager(sim));
        stepCount = 0;
        fixType = LammpsIntegrator::NONE;
        timeStep = 0.005;
        tempRescale = NULL;
        momentum = NULL;
        fixNVE = NULL;
        fixNVT = NULL;
        fixNPT = NULL;
        fixNPH = NULL;
        initialized = false;
    }
	
    /*
     * doStep()
     */
    void LammpsIntegrator::doStep() {
        if(!initialized) {
            lammpsSetup();
            initialized = true;
        }
        char command[512];
        sprintf(command, "run 1");
        lammps_command(mSimulation->getLammpsSim(), command);
        stepCount++;
    }

    /*
     * getStepCount()
     */
    long long LammpsIntegrator::getStepCount() {
        return stepCount;
    }

    /*
     * reset()
     */
    void LammpsIntegrator::reset() {
printf("WARNING : LammpsIntegrator::reset() is NOT implemented yet.\n");
    }

    /*
     * resetStepCount()
     */
    void LammpsIntegrator::resetStepCount() {
        stepCount = 0;
    }

    /*
     * getEventManager()
     */
    IAPIIntegratorEventManager *LammpsIntegrator::getEventManager() {
        return mEventManager;
    }

    /*
     * setNVE()
     */
    void LammpsIntegrator::setNVE(LammpsNVE *nve) {
        fixType = LammpsIntegrator::NVE;
        fixNVE = new LammpsNVE(*nve);

        char command[256];
        sprintf(command,
                "fix %s all %s",
                mSimulation->getFixIDMgr()->getNextID(),
                fixNVE->getFixType());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);
    }

    /*
     * setNVT()
     */
    void LammpsIntegrator::setNVT(LammpsNVT *nvt) {
        fixType = LammpsIntegrator::NVT;
        fixNVT = new LammpsNVT(*nvt);

        char command[256];
        char *fixID = mSimulation->getFixIDMgr()->getNextID();

        if(fixNVT->getDamp() == 0.0) {
            sprintf(command,
                    "fix %s all %s %f %f %f",
                    fixID,
                    fixNVT->getFixType(),
                    fixNVT->getStart(),
                    fixNVT->getStop(),
                    fixNVT->getDamp());
        }
        else {
            sprintf(command,
                    "fix %s all %s %f %f %f drag %f",
                    fixID,
                    fixNVT->getFixType(),
                    fixNVT->getStart(),
                    fixNVT->getStop(),
                    fixNVT->getDamp(),
                    fixNVT->getDrag());
        }
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);

        if(fixNVT->useDOF()) {

            // This next compute_modify is very dangerous.  It is using
            // the knowledge that the nvt fix creates a temp_compute
            // with an id of the fix appended with "_temp".  If the
            // underlying Lammps implementation changes, this will break.
            char *computeID = (char *) malloc((strlen(fixID) + 6) * sizeof(char));
            sprintf(computeID,
                    "%s_temp",
                    fixID);
                        
            sprintf(command,
                    "compute_modify %s extra %d",
                    computeID,
                    fixNVT->getDOF());
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSimulation->getLammpsSim(), command);
        }
    }

    /*
     * setNPT()
     */
    void LammpsIntegrator::setNPT(LammpsNPT *npt) {
        fixType = LammpsIntegrator::NPT;
        fixNPT = new LammpsNPT(*npt);

        char command[256];
        sprintf(command,
                "fix %s all %s %f %f %f",
                mSimulation->getFixIDMgr()->getNextID(),
                fixNPT->getFixType(),
                fixNPT->getStart(),
                fixNPT->getStop(),
                fixNPT->getDamp());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);
    }

    /*
     * setNPH()
     */
    void LammpsIntegrator::setNPH(LammpsNPH *nph) {
        fixType = LammpsIntegrator::NPH;
        fixNPH = new LammpsNPH(*nph);

        char command[256];
        sprintf(command,
                "fix %s all %s",
                mSimulation->getFixIDMgr()->getNextID(),
                fixNPH->getFixType());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);
    }

    /*
     * setTempRescale()
     */
    void LammpsIntegrator::setTempRescale(LammpsTemperatureRescale *rescale) {
        tempRescale = new LammpsTemperatureRescale(*rescale);
    }

    /*
     * setMomentum()
     */
    void LammpsIntegrator::setMomentum(LammpsMomentum *m) {
        momentum = new LammpsMomentum(*m);
    }

    /*
     * setTimestep()
     */
    void LammpsIntegrator::setTimestep(double ts) {
        timeStep = ts;
    }

    /*
     * doSteps()
     */
    void LammpsIntegrator::doSteps(int nSteps) {
        if(!initialized) {
            lammpsSetup();
            initialized = true;
        }
        char command[512];
        sprintf(command, "run %d",
                nSteps);
        lammps_command(mSimulation->getLammpsSim(), command);
        stepCount += nSteps;
    }

    /*
     * lammpsSetup()
     */
    void LammpsIntegrator::lammpsSetup() {
        char command[512];

/*
        // nve
        if(fixType == LammpsIntegrator::NVE) {
            sprintf(command,
                    "fix %s all %s",
                    mSimulation->getFixIDMgr()->getNextID(),
                    fixNVE->getFixType());
        }
        // nph
        else if(fixType == LammpsIntegrator::NPH) {
            sprintf(command,
                    "fix %s all %s",
                    mSimulation->getFixIDMgr()->getNextID(),
                    fixNPH->getFixType());
        }
        // nvt
        else if(fixType == LammpsIntegrator::NVT) {

            char *fixID = mSimulation->getFixIDMgr()->getNextID();

            if(fixNVT->getDamp() == 0.0) {
                sprintf(command,
                        "fix %s all %s %f %f %f",
                        fixID,
                        fixNVT->getFixType(),
                        fixNVT->getStart(),
                        fixNVT->getStop(),
                        fixNVT->getDamp());
            }
            else {
                sprintf(command,
                        "fix %s all %s %f %f %f drag %f",
                        fixID,
                        fixNVT->getFixType(),
                        fixNVT->getStart(),
                        fixNVT->getStop(),
                        fixNVT->getDamp(),
                        fixNVT->getDrag());
            }

            if(fixNVT->useDOF()) {
printf("lammps_command : %s\n", command); fflush(stdout);
                lammps_command(mSimulation->getLammpsSim(), command);

                // This next compute_modify is very dangerous.  It is using
                // the knowledge that the nvt fix creates a temp_compute
                // with an id of the fix appended with "_temp".  If the
                // underlying Lammps implementation changes, this will break.
                char *computeID = (char *) malloc((strlen(fixID) + 6) * sizeof(char));
                sprintf(computeID,
                        "%s_temp",
                        fixID);
                        
                sprintf(command,
                        "compute_modify %s extra %d",
                        computeID,
                        fixNVT->getDOF());
            }
        }
        // npt
        else if(fixType == LammpsIntegrator::NPT) {
            sprintf(command,
                    "fix %s all %s %f %f %f",
                    mSimulation->getFixIDMgr()->getNextID(),
                    fixNPT->getFixType(),
                    fixNPT->getStart(),
                    fixNPT->getStop(),
                    fixNPT->getDamp());
        }
        else {
            printf("ERROR: Unknown integration fix type.\n");
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);
*/

        if(tempRescale != NULL) {
            if(tempRescale->getState() == true) {
                sprintf(command,
                        "fix %s all temp/rescale %d %f %f %f %f",
                        mSimulation->getFixIDMgr()->getNextID(),
                        tempRescale->getSteps(),
                        tempRescale->getStart(),
                        tempRescale->getStop(),
                        tempRescale->getWindow(),
                        tempRescale->getFraction());
printf("lammps_command : %s\n", command); fflush(stdout);
                lammps_command(mSimulation->getLammpsSim(), command);
            }
        }

        if(momentum != NULL) {
            if(momentum->getState() == true) {
                sprintf(command,
                        "fix %s all momentum %d",
                        mSimulation->getFixIDMgr()->getNextID(),
                        momentum->getSteps());
                if(momentum->getType() == LammpsMomentum::LINEAR) {
                    sprintf(command,
                            "%s linear %d %d %d",
                            command,
                            momentum->getXLinearFlag(), 
                            momentum->getYLinearFlag(), 
                            momentum->getZLinearFlag()); 
                }
                else if(momentum->getType() == LammpsMomentum::ANGULAR) {
                    strcat(command, " angular");
                }

printf("lammps_command : %s\n", command); fflush(stdout);
                lammps_command(mSimulation->getLammpsSim(), command);
            }
        }
        // timestep command
        sprintf(command,
                "timestep %f",
                timeStep);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSimulation->getLammpsSim(), command);

    }

}
