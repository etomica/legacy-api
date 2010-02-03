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
    const double LammpsAtomType::DEFAULT_DIAMETER = 1.0;
    const int LammpsAtomType::DEFAULT_TYPE = 1;

/*
    LammpsAtomType::LammpsAtomType() {
        mMass = DEFAULT_MASS;
        mAtomType = 0;
    }

    LammpsAtomType::LammpsAtomType(double m) {
        mMass = m;
        mAtomType = 0;
    }
*/

    LammpsAtomType::LammpsAtomType(int at, int nIndex) {
        mMass = DEFAULT_MASS;
        mAtomType = at;
        nativeIndex = nIndex;
        mDiameter = DEFAULT_DIAMETER;
    }

    LammpsAtomType::LammpsAtomType(int at, int nIndex, double m) {
printf("DEBUG : New atom type -> (glue idx)%d  (native idx)%d\n", at, nIndex);
        mMass = m;
        mAtomType = at;
        nativeIndex = nIndex;
        mDiameter = DEFAULT_DIAMETER;
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

    /*
     * getDiameter()
     */
    double LammpsAtomType::getDiameter() {
        return mDiameter;
    }

    /*
     * setDiameter()
     */
    void LammpsAtomType::setDiameter(double d) {
        mDiameter = d;
    }

    /*
     * getNativeIndex()
     */
    int LammpsAtomType::getNativeIndex() {
        return nativeIndex;
    }

}

