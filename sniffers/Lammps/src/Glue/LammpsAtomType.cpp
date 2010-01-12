/*
 *  LammpsAtomType.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsAtomType.h"

namespace lammpssnifferwrappers
{

    const double LammpsAtomType::DEFAULT_MASS = 1.0;
    const int LammpsAtomType::DEFAULT_TYPE = 1;

    LammpsAtomType::LammpsAtomType() {
        mMass = DEFAULT_MASS;
        mAtomType = 0;
    }

    LammpsAtomType::LammpsAtomType(double m) {
        mMass = m;
        mAtomType = 0;
    }

    LammpsAtomType::LammpsAtomType(int at) {
        mMass = DEFAULT_MASS;
        mAtomType = at;
    }

    LammpsAtomType::LammpsAtomType(int at, double m) {
        mMass = m;
        mAtomType = at;
    }

    /*
     * setIndex
     */
    void LammpsAtomType::setIndex(int index) {
        mAtomType = index;
    }

    /*
     * getIndex
     */
    int LammpsAtomType::getIndex() {
        return mAtomType;
    }

    /*
     * setSpecies()
     */
    void LammpsAtomType::setSpecies(IAPISpecies *newParent) {
        mSpecies = newParent;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *LammpsAtomType::getSpecies() {
        return mSpecies;
    }

    /*
     * setChildIndex()
     */
    void LammpsAtomType::setChildIndex(int newChildIndex) {
printf("WARNING : LammpsAtomType::setChildIndex() is NOT implemented yet.\n");
    }

    /*
     * getChildIndex()
     */
    int LammpsAtomType::getChildIndex() {
printf("WARNING : LammpsAtomType::getChildIndex() is NOT implemented yet.\n");
    }

    /*
     * getMass()
     */
    double LammpsAtomType::getMass() {
        return mMass;
    }

    /*
     * rm()
     */
    double LammpsAtomType::rm() {
printf("WARNING : LammpsAtomType::rm() is NOT implemented yet.\n");
    }

    /*
     * getElement()
     */
    IAPIElement *LammpsAtomType::getElement() {
        return mElement;
    }

}

