/*
 *  TowheeSimulation.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeSimulation.h"
#include "TowheeSimulationEventManager.h"
#include "TowheeIntegrator.h"

extern "C" { void twh_temperature_(int *, double *); }
extern "C" { void twh_boxvclassic_(int *, int *, double *); }

namespace towheesnifferwrappers
{

    TowheeSimulation::TowheeSimulation() {
        mIntegrator = new TowheeIntegrator();
        mEventMgr = new TowheeSimulationEventManager();
        mSpeciesMgr = new TowheeSpeciesManager();
        mSpace = new TowheeSpace(3);
        atomIDMgr = new IndexManager(1);
    }

    /*
     * addBox()
     */
    void TowheeSimulation::addBox(IAPIBox *box) {
        printf("ERROR : TowheeSimulation::addBox(IAPIBox *) is not implemented.\n");
    }

    /*
     * removeBox()
     */
    void TowheeSimulation::removeBox(IAPIBox *box) {
        printf("ERROR : TowheeSimulation::removeBox() is not implemented.\n"); fflush(stdout);
    }

    /*
     * getRandom()
     */
    IAPIRandom *TowheeSimulation::getRandom() {
        printf("WARNING : TowheeSimulation::getRandom() is not implemented.\n");
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *TowheeSimulation::getEventManager() {
        return mEventMgr;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeSimulation::getBox(int index) {
        return mBox.at(index);
    }

    /*
     * getBoxCount()
     */
    int TowheeSimulation::getBoxCount() {
        return mBox.size();
    }

    /*
     * addSpecies()
     */
    void TowheeSimulation::addSpecies(IAPISpecies *species) {
        printf("ERROR : TowheeSimulation::addSpecies(IAPISpecies *) is not implemented.\n");
    }

    /*
     * removeSpecies()
     */
    void TowheeSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        printf("ERROR : TowheeSimulation::removeSpecies(IAPISpecies *) is not implemented.\n");
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
        printf("ERROR : TowheeSimulation::setIntegrator(IAPIIntegrator *) is not implemented.\n");
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
