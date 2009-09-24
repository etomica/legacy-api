/*
 *  GlotzillaAtomType.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaAtomType.h"
#include "GlotzillaAtomPositionDefinitionSimple.h"

namespace glotzwrappers
{

    GlotzillaAtomType::GlotzillaAtomType() {
        mAtomType = 0;
        mMass = 1.0;
        childIndex = 0;
    }

    GlotzillaAtomType::GlotzillaAtomType(int at) {
        mAtomType = at;
        mMass = 1.0;
        childIndex = 0;
    }

    GlotzillaAtomType::GlotzillaAtomType(int at, double mass) {
        mAtomType = at;
        mMass = mass;
        childIndex = 0;
    }

    /*
     * setIndex
     */
    void GlotzillaAtomType::setIndex(int newIndex) {
        mAtomType = newIndex;
    }

    /*
     * getIndex
     */
    int GlotzillaAtomType::getIndex() {
        return mAtomType;
    }

    /*
     * setSpecies()
     */
    void GlotzillaAtomType::setSpecies(IAPISpecies *newParent) {
        species = newParent;
    }

    /*
     * getSpecies()
     */
    IAPISpecies *GlotzillaAtomType::getSpecies() {
        return species;
    }

    /*
     * setChildIndex()
     */
    void GlotzillaAtomType::setChildIndex(int newChildIndex) {
        childIndex = newChildIndex;
    }

    /*
     * getChildIndex()
     */
    int GlotzillaAtomType::getChildIndex() {
        return childIndex;
    }

    /*
     * getMass()
     */
    double GlotzillaAtomType::getMass() {
        return mMass;
    }

    /*
     * rm()
     */
    double GlotzillaAtomType::rm() {
        return 1.0 / mMass;
    }

    /*
     * getElement()
     */
    IAPIElement *GlotzillaAtomType::getElement() {
        return mElement;
    }

}

