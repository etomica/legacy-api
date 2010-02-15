/*
 *  LammpsBox.cpp
 *  API Glue
 *
 *
 */

#include <typeinfo>

#include "library.h"

#include "IAPIMolecule.h"
#include "LammpsBox.h"

namespace lammpssnifferwrappers
{

    const int LammpsBox::INDEX_UNASSIGNED = -1;

    LammpsBox::LammpsBox(LammpsSimulation *sim,
                         IAPIBoundary *boundary,
                         std::vector<LammpsSpecies *> species,
                         std::vector<LammpsMolecule *> molecules) {
        mSim = sim;
        mBoundary = boundary;
        mMolecules = new LammpsMoleculeList();
        mIndex = INDEX_UNASSIGNED;
        mBoxEvtMgr = new LammpsBoxEventManager();
        mLeafList = new LammpsAtomList();
        mMoleListBySpecies = new LammpsMoleculeList();

        for(int i = 0; i < species.size(); i++) {
            if(speciesList.find(species.at(i)) == speciesList.end()) {
                speciesList.insert(std::pair<IAPISpecies *, int>(species.at(i), 0));
            }
        }

        for(int i = 0; i < molecules.size(); i++) {
            mMolecules->addMolecule(molecules.at(i));
            molecules.at(i)->setIndex(mMolecules->getMoleculeCount() - 1);
            speciesList[molecules.at(i)->getType()]++;

            // Set leaf index for atoms
            for(int j = 0; j < molecules.at(i)->getChildList()->getAtomCount(); j++) {
                mLeafList->addAtom(molecules.at(i)->getChildList()->getAtom(j));
                molecules.at(i)->getChildList()->getAtom(j)->setLeafIndex(mLeafList->getAtomCount()-1);
            }
        }

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
        printf("ERROR : LammpsBox::addMolecule(IAPIMolecule *) not implemented.\n");
    }

    /*
     * removeMolecule()
     */
    void LammpsBox::removeMolecule(IAPIMolecule *mole) {
        printf("ERROR : LammpsBox::removeMolecule(IAPIMolecule *) not implemented.\n");
    }

    /*
     * setNMolecules()
     */
    void LammpsBox::setNMolecules(IAPISpecies *species, int numMolecules) {
        printf("ERROR : LammpsBox::setNMolecules(IAPISpecies *, int) not implemented.\n");
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
        printf("ERROR : LammpsBox::setBoundary() not implemented.\n");
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
        printf("ERROR : LammpsBox::addSpeciesNotify(IAPISpecies *) not implemented.\n");
    }

    /*
     * removeSpeciesNotify()
     */
    void LammpsBox::removeSpeciesNotify(IAPISpecies *species) {
        printf("ERROR : LammpsBox::removeSpeciesNotify(IAPISpecies *) not implemented.\n");
    }

}
