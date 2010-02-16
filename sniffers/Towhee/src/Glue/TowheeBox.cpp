/*
 *  TowheeBox.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeBox.h"
#include "TowheeBoxEventManager.h"

extern "C" { void twh_initmol_(int *, int *, int *, int *); }

namespace towheesnifferwrappers
{

    TowheeBox::TowheeBox(IAPIBoundary *b) {
        mIndex = -1;
        mEventManager = new TowheeBoxEventManager();
        mMoleList = new TowheeMoleculeList();
        mMoleListBySpecies = new TowheeMoleculeList();
        mLeafList = new TowheeAtomList();
        mBoundary = b;
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
printf("WARNING : TowheeBox::addMolecule(IAPIMolecule *) is implemented but should not be.\n");
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
        printf("ERROR : TowheeBox::removeMolecule(IAPIMolecule *) is not implemented.\n");
    }

    /*
     * setNMolecules()
     * This method will intentionally be left blank.
     */
    void TowheeBox::setNMolecules(IAPISpecies *species, int numMolecules) {
        printf("ERROR : TowheeBox::removeMolecule(IAPISpecies *, int) is not implemented.\n");
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
        mMoleListBySpecies->clear();
        for(int i = 0; i < mMoleList->getMoleculeCount(); i++) {
            if(mMoleList->getMolecule(i)->getType() == species) {
                mMoleListBySpecies->addMolecule(mMoleList->getMolecule(i));
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
        printf("ERROR : TowheeBox::setBoundary(IAPIBoundary *) is not implemented.\n");
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
        printf("TowheeBox::addSpeciesNotify(IAPISpecies *) is not implemented.\n");
    }

    /*
     * removeSpeciesNotify()
     */
    void TowheeBox::removeSpeciesNotify(IAPISpecies *species) {
        printf("TowheeBox::removeSpeciesNotify(IAPISpecies *) is not implemented.\n");
    }


}
