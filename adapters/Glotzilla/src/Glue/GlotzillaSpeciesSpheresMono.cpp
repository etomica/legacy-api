/*
 *  GlotzillaSpeciesSpheresSpheresMono.cpp
 *  API Glue
 *
 */

#include "GlotzillaSpeciesSpheresMono.h"
#include "GlotzillaAtom.h"
#include "GlotzillaMonatomicMolecule.h"

#include "stdio.h"

namespace glotzwrappers
{

    GlotzillaSpeciesSpheresMono::GlotzillaSpeciesSpheresMono
                                      (IAPISimulation *sim,
                                       IAPIAtomType *aType) : GlotzillaSpecies(sim, NULL) {
        init(aType);
    }

    GlotzillaSpeciesSpheresMono::GlotzillaSpeciesSpheresMono
                                      (IAPISimulation *sim,
                                       IAPIAtomType *aType,
                                       GlotzillaInterfaceConformation *conf) : GlotzillaSpecies(sim, conf) {
        init(aType);
    }

    /*
     * init()
     */
    void GlotzillaSpeciesSpheresMono::init(IAPIAtomType *aType) {
        atomType = aType;
        atomType->setSpecies(this);
        addChildType(aType);
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *GlotzillaSpeciesSpheresMono::makeMolecule() {

        GlotzillaMonatomicMolecule *mole = new GlotzillaMonatomicMolecule(mSim, this);
        mole->addChildAtom(new GlotzillaAtom(mSim, atomType));
        return mole;
    }

    /*
     * addChildType()
     */
    void GlotzillaSpeciesSpheresMono::addChildType(IAPIAtomType *type) {
        typeList.clear();
        GlotzillaSpecies::addChildType(type);
    }

}
