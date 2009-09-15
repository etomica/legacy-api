/*
 *  TowheeBox.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIMolecule.h"
#include "TowheeBox.h"
#include "TowheeSimulation.h"

extern "C" { void twh_initmol_(int *, int *, int *, int *); }

namespace towheewrappers
{

    TowheeBox::TowheeBox() {
        mIndex = -1;
        mBoxEvtMgr = new TowheeBoxEventManager();
        mMolecules = new TowheeMoleculeList();
        mMoleListBySpecies = new TowheeMoleculeList();
        mLeafList = new TowheeAtomList();
    }

    /*
     * setIndex()
     */
    void TowheeBox::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex()
     */
    int TowheeBox::getIndex() {
        return mIndex;
    }

    /*
     * addMolecule()
     */
    void TowheeBox::addMolecule(IAPIMolecule *mole) {
        if(TowheeSimulation::getState() == TowheeSimulation::UNINITIALIZED) {
            mSpeciesCount[mole->getType()] = mSpeciesCount[mole->getType()]  + 1;
            mMolecules->addMolecule(mole);
            mole->setIndex(mMolecules->getMoleculeCount()-1);
            IAPIAtomList *moleSet = mole->getChildList();
            for(int j = 0; j < moleSet->getAtomCount(); j++) {
                moleSet->getAtom(j)->setLeafIndex(mLeafList->getAtomCount());
                mLeafList->addAtom(moleSet->getAtom(j));
            }
        }
        else {
printf("ERROR : TowheeBox::addMolecule() cannot add a molecule after the simulation is initialized.\n"); fflush(stdout);
        }
    }

    /*
     * removeMolecule()
     */
    void TowheeBox::removeMolecule(IAPIMolecule *mole) {
printf("WARNING : TowheeBox::removeMolecule() not implemented.\n"); fflush(stdout);
    }

    /*
     * setNMolecules()
     */
    void TowheeBox::setNMolecules(IAPISpecies *species, int numMolecules) {
        if(TowheeSimulation::getState() == TowheeSimulation::UNINITIALIZED) {
            if(mSpeciesCount[species] < numMolecules) {
                for(int i = mSpeciesCount[species]; i < numMolecules; i++)
                    addNewMolecule(species);
            }
            else if(mSpeciesCount[species] > numMolecules) {
                printf("WARNING : TowheeBox::setNMolecules() cannot remove molecules.\n"); fflush(stdout);
            }
            mSpeciesCount[species] = numMolecules;
        }
        else {
printf("ERROR : TowheeBox::setNMolecules() cannot be called after the simulation is initialized.\n"); fflush(stdout);
        }
    }

    /*
     * getNMolecules()
     */
    int TowheeBox::getNMolecules(IAPISpecies *species) {
        int numMolecules;

        if(TowheeSimulation::getState() == TowheeSimulation::UNINITIALIZED) {
            numMolecules = mSpeciesCount[species];
        }
        else {
            int get = GLB_GET;
            int idx = mIndex + 1;
            int speciesIndex = species->getIndex() + 1;

            twh_initmol_(&get, &idx, &speciesIndex, &numMolecules);
        }

        return numMolecules;

    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList(IAPISpecies *species) {
        mMoleListBySpecies->clear();

        for(int i = 0; i < mMolecules->getMoleculeCount(); i++) {
            IAPIMolecule *mole = mMolecules->getMolecule(i);
            if(mole->getType() == species) {
                mMoleListBySpecies->addMolecule(mole);
            }
        }
        return mMoleListBySpecies;
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList() {
        return mMolecules;
    }

    /*
     * getLeafList()
     */
    IAPIAtomList *TowheeBox::getLeafList() {

        return mLeafList;
    }

    /*
     * getBoundary()
     */
    IAPIBoundary *TowheeBox::getBoundary() {
        return mBoundary;
    }

    /*
     * setBoundary()
     */
    void TowheeBox::setBoundary(IAPIBoundary *boundary) {
        mBoundary = boundary;
    }

    /*
     * getEventManager()
     */
    IAPIBoxEventManager *TowheeBox::getEventManager() {
        return mBoxEvtMgr;
    }

    /*
     * addSpeciesNotify()
     */
    void TowheeBox::addSpeciesNotify(IAPISpecies *species) {
        mSpeciesCount.insert(std::pair<IAPISpecies *, int>(species, 0));
    }

    /*
     * removeSpeciesNotify()
     */
    void TowheeBox::removeSpeciesNotify(IAPISpecies *species) {
printf("WARNING : TowheeBox::removeSpeciesNotify() not implemented.\n"); fflush(stdout);
    }

    /*
     * addNewMolecule()
     */
    void TowheeBox::addNewMolecule(IAPISpecies *species) {
        if(TowheeSimulation::getState() == TowheeSimulation::UNINITIALIZED) {
            IAPIMolecule *mole = species->makeMolecule();
            addMolecule(mole);
        }
        else {
printf("ERROR : Cannot create a new molecule after the simulation is initialized.\n"); fflush(stdout);
        }
    }

}
