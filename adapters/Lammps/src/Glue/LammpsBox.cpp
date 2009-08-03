/*
 *  LammpsBox.cpp
 *  API Glue
 *
 *
 */

#include <typeinfo>

#include "library.h"

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIMolecule.h"
#include "LammpsAtomList.h"
#include "LammpsBox.h"
#include "LammpsBoxEventManager.h"
#include "LammpsRegionBlock.h"
#include "LammpsSpecies.h"
#include "LammpsBoundaryDeformable.h"

namespace lammpswrappers
{

    const int LammpsBox::INDEX_UNASSIGNED = -1;
    LammpsBox *LammpsBox::mInstance = NULL;

    LammpsBox *LammpsBox::instance(IAPISimulation *sim) {
        if(mInstance == NULL) {
            mInstance = new LammpsBox(sim);
        }
        return mInstance;
    }

    LammpsBox::LammpsBox(IAPISimulation *sim) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        mMolecules = new LammpsMoleculeList();
        mIndex = INDEX_UNASSIGNED;
        mBoxEvtMgr = new LammpsBoxEventManager();
        objectManager = new ObjectManager();
        mLeafList = new LammpsAtomList();
        mMoleListBySpecies = new LammpsMoleculeList();
    }

    /*
     * setIndex()
     */
    void LammpsBox::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex()
     */
    int LammpsBox::getIndex() {
        return mIndex;
    }

    /*
     * addMolecule()
     */
    void LammpsBox::addMolecule(IAPIMolecule *mole) {

        speciesList[mole->getType()] = speciesList[mole->getType()] + 1;
        mMolecules->addMolecule(mole);
        // Next line assumes new molecule added to end of list
        mole->setIndex(mMolecules->getMoleculeCount() - 1);

    }

    /*
     * removeMolecule()
     */
    void LammpsBox::removeMolecule(IAPIMolecule *mole) {

        printf("ERROR : LammpsBox::removeMolecule() should never be called.\n");
    }

    /*
     * setNMolecules()
     */
    void LammpsBox::setNMolecules(IAPISpecies *species, int numMolecules) {
        if(mSim->getState() == LammpsSimulation::UNINITIALIZED) {
            lammpsSetup();
            mSim->setState(LammpsSimulation::CREATING_ATOMS);
            mSim->lammpsSetup();
        }

        if(speciesList.find(species) ==  speciesList.end()) {
            printf("ERROR : LammpsBox::setNMolecules() : species not added to box yet.\n");
        }
        else {
            if(speciesList[species] < numMolecules) {
                for(int i = speciesList[species]; i < numMolecules; i++) {
                    addNewMolecule(species);
                }
//                speciesList[species] = numMolecules;
            }
            else if(speciesList[species] > numMolecules) {
                printf("Unable to delete molecules for the species once some molecules\n");
                printf("of the species have already been added to the simulation.\n"); fflush(stdout);
            }
        }
    }

    /*
     * getNMolecules()
     */
    int LammpsBox::getNMolecules(IAPISpecies *species) {
        return speciesList[species];
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *LammpsBox::getMoleculeList(IAPISpecies *species) {

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
    IAPIMoleculeList *LammpsBox::getMoleculeList() {

        return mMolecules;
    }

    /*
     * getLeafList()
     */
    IAPIAtomList *LammpsBox::getLeafList()
    {
        mLeafList->clear();

        for(int i = 0; i < mMolecules->getMoleculeCount(); i++) {
            IAPIMolecule *mole = mMolecules->getMolecule(i);
            IAPIAtomList *moleSet = mole->getChildList();
            for(int j = 0; j < moleSet->getAtomCount(); j++) {
                mLeafList->addAtom(moleSet->getAtom(j));
            }
        }

        return mLeafList;

    }

    /*
     * getBoundary()
     */
    IAPIBoundary *LammpsBox::getBoundary() {

        if(mSim->getState()) {
        // Set mBoundary here
        }
        return mBoundary;
    }

    /*
     * setBoundary()
     */
    void LammpsBox::setBoundary(IAPIBoundary *boundary) {
        if(mSim->getState()) {
            printf("ERROR : LammpsBox::setBoundary cannot be called after simulation is initialized/\n");
        }
        else {
            mBoundary = boundary;
        }
    }

    /*
     * getEventManager()
     */
    IAPIBoxEventManager *LammpsBox::getEventManager() {
        return mBoxEvtMgr;
    }

    /*
     * addSpeciesNotify()
     */
    void LammpsBox::addSpeciesNotify(IAPISpecies *species) {

        if(mSim->getState()) {
            printf("ERROR : LammpsBox::addSpeciesNotify() cannot be called after the simulation is initialized.\n");
        }
        else {
            // Only add species if not previously added
            if(speciesList.find(species) == speciesList.end()) {
                speciesList.insert(std::pair<IAPISpecies *, int>(species, 0));
            }
        }
    }

    /*
     * removeSpeciesNotify()
     */
    void LammpsBox::removeSpeciesNotify(IAPISpecies *species) {
        if(mSim->getState() == LammpsSimulation::UNINITIALIZED) {
            speciesList.erase(speciesList.find(species));
        }
        else {
            printf("ERROR : LammpsBox::removeSpeciesNotify() cannot be called after the simulation is initialized.\n");
        }
    }

    /*
     * addNewMolecule()
     */
    IAPIMolecule *LammpsBox::addNewMolecule(IAPISpecies *species) {
        if(mSim->getState() == LammpsSimulation::INITIALIZED) {
            printf("ERROR : LammpsBox::addNewMolecule() cannot be called after the simulation is initialized.\n");
        }
        else {
            IAPIMolecule *mole = species->makeMolecule();
            addMolecule(mole);
        }
    }

    /**
     * lammpsSetup()
     */
    void LammpsBox::lammpsSetup() {

        char command[512];

        if(typeid(*mBoundary) != typeid(LammpsBoundaryDeformable)) {

            // Initialize Boundary
            dynamic_cast<LammpsBoundary *>(mBoundary)->lammpsSetup();
        }

        // Issue region command
        IAPIVector *v = mBoundary->getBoxSize();

        // Lammps checks box validity and hi/lo values in
        // z direction for 2D cannot be the same.
        LammpsRegionBlock *region;
        IAPIVector *regionMin;
        IAPIVector *regionMax;

        if(mSim->getSpace()->getD() == 2) {
            double min[2] = {-v->getX(0) / 2.0, -v->getX(1) / 2.0};
            regionMin = mSim->getSpace()->makeVector(min);
            double max[2] = {v->getX(0) / 2.0, v->getX(1) / 2.0};
            regionMax = mSim->getSpace()->makeVector(max);
        }
        else if(mSim->getSpace()->getD() == 3) {
            double min[3] = {-v->getX(0) / 2.0, -v->getX(1) / 2.0, -v->getX(2) / 2.0};
            regionMin = mSim->getSpace()->makeVector(min);
            double max[3] = {v->getX(0) / 2.0, v->getX(1) / 2.0, v->getX(2) / 2.0};
            regionMax = mSim->getSpace()->makeVector(max);
        }

        region = new LammpsRegionBlock(mSim, regionMin, regionMax);

        // Issue create_box command
        sprintf(command,
                "create_box %d %s",
                numberAtomTypes(),
                region->getRegionID());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

        if(typeid(*mBoundary) == typeid(LammpsBoundaryDeformable)) {
            // Initialize Boundary
            dynamic_cast<LammpsBoundaryDeformable *>(mBoundary)->lammpsSetup();
        }

    }

    /*
     * numberAtomTypes()
     */
    int LammpsBox::numberAtomTypes() {

        int uniqueTypes = 0;
        std::vector<int> atomTypeList;

        int specieCount = mSim->getSpeciesManager()->getSpeciesCount();

        for(int i = 0; i < specieCount; i++) {
            IAPISpecies *specie = mSim->getSpeciesManager()->getSpecies(i);
            for(int j = 0; j < specie->getAtomTypeCount(); j++) {
                IAPIAtomType *type = specie->getAtomType(j);
                int atomType = type->getIndex();
                bool matchFound = false;
                for(int k = 0; k < atomTypeList.size(); k++) {
                    if(atomTypeList.at(k) == atomType) {
                        matchFound = true;
                        break;
                    }
                }
                if(matchFound == false) {
                    atomTypeList.push_back(atomType);
                    uniqueTypes++;
                }
            }
        }

        return uniqueTypes;

    }

}
