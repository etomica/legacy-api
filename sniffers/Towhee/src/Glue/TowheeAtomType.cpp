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
     *   NOTE : Towhee's atom type index would be this index + 1
     */
    void TowheeAtomType::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex
     *   NOTE : Towhee's atom type index would be this index + 1
     */
    int TowheeAtomType::getIndex() {
        return mIndex;
    }

    /*
     * setSpecies()
     */
    void TowheeAtomType::setSpecies(IAPISpecies *newParent) {
        printf("WARNING : TowheeAtomType::setSpecies(IAPISpecies *) is not implemented.\n");
    }

    /*
     * setSnifferSpecies()
     */
    void TowheeAtomType::setSnifferSpecies(IAPISpecies *newParent) {
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
        printf("TowheeAtomType::setChildIndex(int) not implemented.\n");
    }

    /*
     * getChildIndex()
     */
    int TowheeAtomType::getChildIndex() {
        printf("TowheeAtomType::getChildIndex(int) not implemented.\n");
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
        return 1.0/getMass();
    }

    /*
     * getElement()
     */
    IAPIElement *TowheeAtomType::getElement() {
        return mElement;
    }

}

