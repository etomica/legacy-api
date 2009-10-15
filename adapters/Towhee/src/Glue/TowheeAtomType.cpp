/*
 *  TowheeAtomType.cpp
 *  API Glue
 *
 */

#include "preproc.h"

#include "TowheeAtomType.h"

extern "C" { void twh_mass_(int *, int *, double *); }

namespace towheewrappers
{

    TowheeAtomType::TowheeAtomType(int index) {
        setup(index, 1.0);
    }

    TowheeAtomType::TowheeAtomType(int index, double mass) {
        setup(index, mass);
    }

    /*
     * setup()
     */
    void TowheeAtomType::setup(int index, double m) {
        mIndex = index;
        int set = GLB_SET;
        int idx = mIndex + 1;
        double mass = m;
        twh_mass_(&set, &idx, &mass);
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
        int get = GLB_GET;
        int index = mIndex + 1;
        double mass;
        twh_mass_(&get, &index, &mass);

        return mass;

    }

    /*
     * rm()
     */
    double TowheeAtomType::rm() {
        return 1.0 / getMass();
    }

    /*
     * getElement()
     */
    IAPIElement *TowheeAtomType::getElement() {
        return mElement;
    }

}

