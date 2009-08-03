/*
 *  GlotzillaSpecies.cpp
 *  API Glue
 *
 */

#include "GlotzillaAtomPositionDefinitionSimple.h"
#include "GlotzillaSimulation.h"
#include "GlotzillaSpecies.h"

#include "stdio.h"

namespace glotzwrappers
{

    GlotzillaSpecies::GlotzillaSpecies(IAPISimulation *sim,
                                       GlotzillaInterfaceConformation *conform) {
        mConformation = conform;
        mSim = dynamic_cast<GlotzillaSimulation *>(sim);
        mIndex = -1;
    }

    /*
     * setIndex()
     */
    void GlotzillaSpecies::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getIndex()
     */
    int GlotzillaSpecies::getIndex() {
        return mIndex;
    }

    /*
     * addChildType()
     */
    void GlotzillaSpecies::addChildType(IAPIAtomType *type) {
        typeList.push_back(type);
    }

    /*
     * removeChildType()
     */
    void GlotzillaSpecies::removeChildType(IAPIAtomType *type) {

        for(int i = 0; i < typeList.size(); i++) {
            if(typeList.at(i)->getIndex() == type->getIndex()) {
                typeList.erase(typeList.begin()+i, typeList.begin()+i+1);
            }
        }

    }

    /*
     * getAtomType()
     */
    IAPIAtomType *GlotzillaSpecies::getAtomType(int index) {
        IAPIAtomType *aType = NULL;

        if(index < typeList.size()) {
            aType = typeList.at(index);
        }
        return aType;
    }

    /*
     * getAtomTypeCount()
     */
    int GlotzillaSpecies::getAtomTypeCount() {
        return typeList.size();
    }

    /*
     * initializeConformation()
     */
    void GlotzillaSpecies::initializeConformation(IAPIMolecule *molecule) {
        mConformation->initializePositions(molecule->getChildList());
    }

}
