/*
 *  LammpsMolecule.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsAtom.h"
#include "LammpsAtomList.h"
#include "LammpsMolecule.h"

namespace lammpswrappers
{

    LammpsMolecule::LammpsMolecule(IAPISimulation *sim, IAPISpecies *species) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        mAtomType = species;
        nativeMoleculeID = mSim->getMoleculeIDMgr()->getNextID();
        mAtoms = new LammpsAtomList();
        mIndex = -1;
    }

    /*
     * getIndex()
     */
    int LammpsMolecule::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void LammpsMolecule::setIndex(int index) {
        mIndex = index;
    }

    /*
     * addChildAtom
     */
    void LammpsMolecule::addChildAtom(IAPIAtom *atom) {
        mAtoms->addAtom(atom);
    }

    /*
     * removeChildAtom
     */
    void LammpsMolecule::removeChildAtom(IAPIAtom *atom) {
printf("WARNING : LammpsMolecule::removeChildAtom() is NOT implemented yet\n");
    }

    /*
     * getChildList
     */
    IAPIAtomList *LammpsMolecule::getChildList() {
        return mAtoms;
    }

    /*
     * getType()
     */
    IAPISpecies *LammpsMolecule::getType() {
        return mAtomType;
    }

    /*
     * setVelocity()
     */
    void LammpsMolecule::setVelocity(IAPIVector *velocity) {

        for(int i = 0; i < mAtoms->getAtomCount(); i++) {
            IAPIAtom *atom = mAtoms->getAtom(i);
            dynamic_cast<LammpsAtom *>(atom)->getVelocity()->E(velocity);
        }

    }

}
