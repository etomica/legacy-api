/*
 *  TowheeAtomType.cpp
 *  API Glue
 *
 */

#include "TowheeAtomType.h"

namespace towheewrappers
{

    TowheeAtomType::TowheeAtomType(int index) {
        mIndex = index;
    }

    /*
     * setIndex
     */
    void TowheeAtomType::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex
     */
    int TowheeAtomType::getIndex() {
        return mIndex;
    }

    /*
     * setSpecies()
     */
    void TowheeAtomType::setSpecies(IAPISpecies *newParent) {
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeAtomType::getSpecies() {
    }

    /*
     * setChildIndex()
     */
    void TowheeAtomType::setChildIndex(int newChildIndex) {
    }

    /*
     * getChildIndex()
     */
    int TowheeAtomType::getChildIndex() {
    }

    /*
     * getMass()
     */
    double TowheeAtomType::getMass() {
    }

    /*
     * rm()
     */
    double TowheeAtomType::rm() {
    }

}

