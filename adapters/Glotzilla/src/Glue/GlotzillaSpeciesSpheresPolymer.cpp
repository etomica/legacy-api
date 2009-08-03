/*
 *  GlotzillaSpeciesSpheresPolymer.cpp
 *  API Glue
 *
 */

#include "GlotzillaSpeciesSpheresPolymer.h"
#include "GlotzillaAtom.h"
#include "GlotzillaPolymer.h"

#include "stdio.h"

namespace glotzwrappers
{

    GlotzillaSpeciesSpheresPolymer::GlotzillaSpeciesSpheresPolymer(IAPISimulation *sim) : GlotzillaSpecies(sim, NULL) {
    }

    GlotzillaSpeciesSpheresPolymer::GlotzillaSpeciesSpheresPolymer(IAPISimulation *sim,
                                                      GlotzillaInterfaceConformation *conf) : GlotzillaSpecies(sim, conf) {
    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *GlotzillaSpeciesSpheresPolymer::makeMolecule() {

        GlotzillaPolymer *poly = new GlotzillaPolymer(mSim, this);
        for(int i = 0; i < typeList.size(); i++) {

            poly->addChildAtom(new GlotzillaAtom(mSim, getAtomType(i)));
        }
        return poly;
    }

}
