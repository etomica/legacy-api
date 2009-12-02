/*
 *  TowheeAtomType.cpp
 *  API Glue
 *
 */

#include "preproc.h"
#include "stdio.h"

#include "TowheeAtomType.h"

extern "C" { void twh_mass_(int *, int *, double *); }

namespace towheesnifferwrappers
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
        mSpecies = newParent;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *TowheeAtomType::getSpecies() {
        return mSpecies;
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
        int get = GLB_GET;
        int idx = mIndex + 1;
        double mass;
        twh_mass_(&get, &idx, &mass);
        return mass;
    }

    /*
     * rm()
     */
    double TowheeAtomType::rm() {
    }

    /*
     * getElement()
     */
    IAPIElement *TowheeAtomType::getElement() {
        return mElement;
    }

}

