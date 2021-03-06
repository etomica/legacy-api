/*
 *  GlotzillaMolecule.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaAtomList.h"
#include "GlotzillaMolecule.h"
#include "GlotzillaMonatomicMolecule.h"
#include "GlotzillaPolymer.h"

/*
IMPORTANT : NEED TO CHANGE IMPLEMENTATION
childList should not live here.  When requesting atoms in molecule,
need to go right to the simulation to get the list.
*/
namespace glotzwrappers
{

    GlotzillaMolecule::GlotzillaMolecule(IAPISimulation *sim, IAPISpecies *species) {
       mSim = dynamic_cast<GlotzillaSimulation *>(sim);
       mSpecies = species;
       mAtomList = new GlotzillaAtomList();
    }

    /*
     * getIndex()
     */
    int GlotzillaMolecule::getIndex() {
        return mSim->getGlotzillaSim()->gParticle.GetIndexOf(getGlotzParticle());
    }

    /*
     * setIndex()
     */
    void GlotzillaMolecule::setIndex(int index) {
    }

    /*
     * getType()
     */
    IAPISpecies *GlotzillaMolecule::getType() {
        return mSpecies;
    }

}
