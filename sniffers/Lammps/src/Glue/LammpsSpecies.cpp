/*
 *  LammpsSpecies.cpp
 *  API Glue
 *
 */

#include "stdio.h"

//#include "LammpsConformation.h"
#include "LammpsSpecies.h"

//
// IMPORTANT : A lot of these methods should NOT perform functionality
//             if simulation is already initialized!
//
namespace lammpssnifferwrappers
{

/*
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
*/
    LammpsSpecies::LammpsSpecies(LammpsSimulation *sim, std::vector<LammpsAtomType *>tList) {
        mSim = sim;
        mIndex = -1;

        bool inList[tList.size()];
        for(int i = 0; i < tList.size(); i++) {
            inList[i] = false;
        }
        for(int i = 0; i < tList.size(); i++) {
            if(inList[i] == false) {
                typeList.push_back(tList[i]);
                inList[i] = true;
                int tCount = 1;
                for(int j = i+1; j < tList.size(); j++) {
                    if(tList[i] == tList[j]) {
                        inList[j] = true;
                        tCount++;
                    }
                }
                typeCount.push_back(tCount);
            }
        }

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

    /*
     * makeMolecule()
     */
    IAPIMolecule *LammpsSpecies::makeMolecule() {
        printf("WARNING : LammpsSpecies::makeMolecule() is not implemented.\n");
    }

    /*
     * setConformation()
     */
    void LammpsSpecies::setConformation(LammpsInterfaceConformation *c) {
        mConformation = c;
    }

}
