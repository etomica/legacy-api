/*
 *  LammpsSpecies.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsConformation.h"
#include "LammpsSpecies.h"

//
// IMPORTANT : A lot of these methods should NOT perform functionality
//             if simulation is already initialized!
//
namespace lammpswrappers
{

    LammpsSpecies::LammpsSpecies(IAPISimulation *sim,
                                 LammpsInterfaceConformation *conform) {
        if(conform == NULL) {
            new LammpsConformation(sim);
        }
        else {
            mConformation = conform;
        }
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        mIndex = -1;
    }

    /*
     * getIndex()
     */
    int LammpsSpecies::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void LammpsSpecies::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getAtomTypeCount()
     */
    int LammpsSpecies::getAtomTypeCount() {
        return typeList.size();
    }

    /*
     * getAtomType()
     */
    IAPIAtomType *LammpsSpecies::getAtomType(int index) {
        IAPIAtomType *aType = NULL;

        if(index < typeList.size()) {
            aType = typeList.at(index);
        }
        return aType;
    }

    /*
     * initializeConformation()
     */
    void LammpsSpecies::initializeConformation(IAPIMolecule *molecule) {
        mConformation->initializePositions(molecule->getChildList());
    }

}
