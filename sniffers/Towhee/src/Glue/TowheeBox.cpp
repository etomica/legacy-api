/*
 *  TowheeBox.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIMolecule.h"

#include "TowheeBox.h"
#include "TowheeBoxEventManager.h"

extern "C" { void twh_initmol_(int *, int *, int *, int *); }

namespace towheesnifferwrappers
{

    TowheeBox::TowheeBox() {
        mIndex = -1;
        mEventManager = new TowheeBoxEventManager();
        mMoleList = new TowheeMoleculeList();
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
        mMoleList->addMolecule(mole);
        mole->setIndex(mMoleList->getMoleculeCount()-1);
        TowheeAtomList *atomList = dynamic_cast<TowheeAtomList *>(mole->getChildList());
        for(int i = 0; i < atomList->getAtomCount(); i++) {
            mLeafList->addChildAtom(atomList->getAtom(i));
            atomList->getAtom(i)->setLeafIndex(mLeafList->getAtomCount()-1);
        }
    }

    /*
     * removeMolecule()
     */
    void TowheeBox::removeMolecule(IAPIMolecule *mole) {
        // Do not implement this method
    }

    /*
     * setNMolecules()
     * This method will intentionally be left blank.
     */
    void TowheeBox::setNMolecules(IAPISpecies *species, int numMolecules) {
        // Do not implement this method
    }

    /*
     * getNMolecules()
     */
    int TowheeBox::getNMolecules(IAPISpecies *species) {

        int get = GLB_GET;
        int idx = mIndex + 1;
        int speciesIndex = species->getIndex() + 1;
        int numMolecules;

        twh_initmol_(&get, &idx, &speciesIndex, &numMolecules);

        return numMolecules;
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList(IAPISpecies *species) {
printf("in getMoleculeList()\n"); fflush(stdout);
printf("  before clear()\n"); fflush(stdout);
        mMoleListBySpecies->clear();
printf("  after clear : %d\n", mMoleList->getMoleculeCount()); fflush(stdout);
        for(int i = 0; i < mMoleList->getMoleculeCount(); i++) {
printf("  idx = %d\n", i); fflush(stdout);
            if(mMoleList->getMolecule(i)->getType() == species) {
printf("  before addMolecule()\n"); fflush(stdout);
                mMoleListBySpecies->addMolecule(mMoleList->getMolecule(i));
printf("  after addMolecule()\n"); fflush(stdout);
            }
        }
        return mMoleListBySpecies;
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList() {
        return mMoleList;
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
        return mEventManager;
    }

    /*
     * addSpeciesNotify()
     */
    void TowheeBox::addSpeciesNotify(IAPISpecies *species) {
    }

    /*
     * removeSpeciesNotify()
     */
    void TowheeBox::removeSpeciesNotify(IAPISpecies *species) {
    }


}
