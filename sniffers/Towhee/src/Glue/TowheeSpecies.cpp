/*
 *  TowheeSpecies.cpp
 *  API Glue
 *
 */

#include "TowheeSpecies.h"

namespace towheesnifferwrappers
{

    TowheeSpecies::TowheeSpecies(TowheeSimulationSniffer *sim) {
        mSim = sim;
    }

    /*
     * setIndex()
     */
    void TowheeSpecies::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int TowheeSpecies::getIndex() {
        return mIndex;
    }

    /*
     * getAtomType()
     */
    IAPIAtomType *TowheeSpecies::getAtomType(int index) {
        return mTypeList.at(index);
    }

    /*
     * getAtomTypeCount()
     */
    int TowheeSpecies::getAtomTypeCount() {
        return mTypeList.size();
    }

    /*
     * initializeConformation()
     */
    void TowheeSpecies::initializeConformation(IAPIMolecule *molecule) {
        mConformation->initializePositions(molecule->getChildList());
    }

}
