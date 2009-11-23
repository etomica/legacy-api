/*
 *  GlotzillaSimulation.cpp
 *  API Glue
 *
 */

#include "GlotzillaSimulation.h"
#include "GlotzillaSimulationEventManager.h"
#include "GlotzillaBox.h"
#include "GlotzillaSpeciesManager.h"

namespace glotzwrappers
{

    GlotzillaSimulation::GlotzillaSimulation(int dim) {
        // Create a simulation
        mGlotzSim = new glotzmd::Simulation();
        mSpace = new GlotzillaSpace(dim);
        init();

    }

    GlotzillaSimulation::GlotzillaSimulation(glotzmd::Simulation* sim) : mGlotzSim(sim) {
        init();
    }

    GlotzillaSimulation::~GlotzillaSimulation() {
printf("WARNING : GlotzillaSimulation::~GlotzillaSimulation() is NOT implemented.\n");
        // delete all boxs in simulation
        // probably leak the underlying glotzilla sim.  yay
    }

    /*
     * init()
     */
    void GlotzillaSimulation::init() {
        eventManager = new GlotzillaSimulationEventManager();
        mSpeciesManager = new GlotzillaSpeciesManager();
        mRand = new GlotzillaRandom();

        // Create a box
        addBox(GlotzillaBox::instance(mGlotzSim));

        mIntegrator = NULL;
    }

    /*
     * addBox()
     */
    void GlotzillaSimulation::addBox(IAPIBox *box) {
        if(mBox.size() == 0) {
            // Add box to list
            mBox.push_back(box);
            box->setIndex(mBox.size()-1);
            mSpeciesManager->boxAddedNotify(box);
        }
        else {
            printf("The Simulation already contains a box.\n"); fflush(stdout);
        }
    }

    /*
     * removeBox()
     */
    void GlotzillaSimulation::removeBox(IAPIBox *box) {

        // Need to do something to simulation here

        // Remove box from list
        int index = -1;

        for(int i = 0; i < mBox.size(); i++) {
            if(mBox.at(i) == box) {
                index = i;
                break;
            }
        }

        mBox.erase(mBox.begin()+index, mBox.begin()+index+1);
    }

    /*
     * getRandom()
     */
    IAPIRandom *GlotzillaSimulation::getRandom() {
        return mRand;
    }

    /*
     * getEventManager()
     */
    IAPISimulationEventManager *GlotzillaSimulation::getEventManager() {
        return(eventManager);
    }

    /*
     * getBox()
     */
    IAPIBox *GlotzillaSimulation::getBox(int index) {
        return mBox.at(index);
    }

    /*
     * getBoxCount()
     */
    int GlotzillaSimulation::getBoxCount() {
        return mBox.size();
    }

    /*
     * addSpecies()
     */
    void GlotzillaSimulation::addSpecies(IAPISpecies *species) {
        mSpeciesManager->addSpecies(species);
    }

    /*
     * removeSpecies()
     */
    void GlotzillaSimulation::removeSpecies(IAPISpecies *removedSpecies) {
        mSpeciesManager->removeSpecies(removedSpecies);
    }

    /*
     * getSpeciesCount()
     */
    int GlotzillaSimulation::getSpeciesCount() {
        return mSpeciesManager->getSpeciesCount();
    }

    /*
     * getSpecies()
     */
    IAPISpecies *GlotzillaSimulation::getSpecies(int index) {
        return mSpeciesManager->getSpecies(index);
    }

    /*
     * getIntegrator()
     */
    IAPIIntegrator *GlotzillaSimulation::getIntegrator() {
        return mIntegrator;
    }

    /*
     * setIntegrator()
     */
    void GlotzillaSimulation::setIntegrator(IAPIIntegrator *integrator) {
        mIntegrator = integrator;
    }

    /*
     * getPotentialEnergy()
     */
    double GlotzillaSimulation::getPotentialEnergy() {
        return mGlotzSim->ComputePotentialEnergy();
    }

    /*
     * getKineticEnergy()
     */
    double GlotzillaSimulation::getKineticEnergy() {
        return mGlotzSim->ComputeKineticEnergy();
    }

    /*
     * getTotalEnergy()
     */
    double GlotzillaSimulation::getTotalEnergy() {
        return mGlotzSim->ComputeTotalEnergy();
    }

    /*
     * getSpace()
     */
    GlotzillaSpace *GlotzillaSimulation::getSpace() {
        return mSpace;
    }

}
