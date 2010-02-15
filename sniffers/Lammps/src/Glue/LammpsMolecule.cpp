/*
 *  LammpsMolecule.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsAtom.h"
#include "LammpsMolecule.h"

namespace lammpssnifferwrappers
{

    LammpsMolecule::LammpsMolecule(int nIndex) {

        mSpecies = NULL;
        nativeMoleculeID = nIndex;
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
        printf("WARNING : LammpsMolecule::addChildAtom(IAPIAtom *) is implemented but should not be.\n");
        mAtoms->addAtom(atom);
    }

    /*
     * removeChildAtom
     */
    void LammpsMolecule::removeChildAtom(IAPIAtom *atom) {
        printf("ERROR : LammpsMolecule::removeChildAtom(IAPIAtom *) is not implemented yet\n");
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
        return mSpecies;
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

    /*
     * getNativeIndex()
     */
    int LammpsMolecule::getNativeIndex() {
        return nativeMoleculeID;
    }

    /*
     * setSpecies()
     */
    void LammpsMolecule::setSpecies(IAPISpecies *species) {
        mSpecies = species;
    }

}
