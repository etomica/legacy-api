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
//#include "LammpsRegionBlock.h"
//#include "LammpsSpecies.h"
//#include "LammpsBoundaryDeformable.h"

namespace lammpssnifferwrappers
{

    const int LammpsBox::INDEX_UNASSIGNED = -1;

    LammpsBox::LammpsBox(LammpsSimulation *sim) {
        mSim = sim;
        mMolecules = new LammpsMoleculeList();
        mIndex = INDEX_UNASSIGNED;
        mBoxEvtMgr = new LammpsBoxEventManager();
//        objectManager = new ObjectManager();
        mLeafList = new LammpsAtomList();
//        mMoleListBySpecies = new LammpsMoleculeList();
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
        mMolecules->addMolecule(mole);
        mole->setIndex(mMolecules->getMoleculeCount() - 1);
        speciesList[mole->getType()]++;

        // Set leaf index for atoms
        for(int i = 0; i < mole->getChildList()->getAtomCount(); i++) {
            mLeafList->addAtom(mole->getChildList()->getAtom(i));
            mole->getChildList()->getAtom(i)->setLeafIndex(mLeafList->getAtomCount());
        }
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
printf("LammpsBox::getNMolecules NOT implemented yet.\n");
/*
        return speciesList[species];
*/
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *LammpsBox::getMoleculeList(IAPISpecies *species) {

printf("LammpsBox::getMoleculeList(IAPISpecies) NOT implemented yet.\n");
/*
        mMoleListBySpecies->clear();

        for(int i = 0; i < mMolecules->getMoleculeCount(); i++) {
            IAPIMolecule *mole = mMolecules->getMolecule(i);
            if(mole->getType() == species) {
                mMoleListBySpecies->addMolecule(mole);
            }
        }
        return mMoleListBySpecies;
*/
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
    IAPIAtomList *LammpsBox::getLeafList() {
        return mLeafList;
    }

    /*
     * getBoundary()
     */
    IAPIBoundary *LammpsBox::getBoundary() {

        return mBoundary;
    }

    /*
     * setBoundary()
     */
    void LammpsBox::setBoundary(IAPIBoundary *boundary) {
        mBoundary = boundary;
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
        // Only add species if not previously added
        if(speciesList.find(species) == speciesList.end()) {
            speciesList.insert(std::pair<IAPISpecies *, int>(species, 0));
        }
    }

    /*
     * removeSpeciesNotify()
     */
    void LammpsBox::removeSpeciesNotify(IAPISpecies *species) {
printf("LammpsBox::removeSpeciesNotify(IAPISpecies) NOT implemented yet.\n");
/*
        if(mSim->getState() == LammpsSimulation::UNINITIALIZED) {
            speciesList.erase(speciesList.find(species));
        }
        else {
            printf("ERROR : LammpsBox::removeSpeciesNotify() cannot be called after the simulation is initialized.\n");
        }
*/
    }

    /*
     * addNewMolecule()
     */
    IAPIMolecule *LammpsBox::addNewMolecule(IAPISpecies *species) {
        IAPIMolecule *mole = species->makeMolecule();
        addMolecule(mole);
    }

}
