/*
 *  GlotzillaPotentialDzugutov.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialDzugutov.h"

namespace glotzwrappers
{

    GlotzillaPotentialDzugutov::GlotzillaPotentialDzugutov() {
        mPotential = new glotzmd::DzugutovPotential;
    }

    /*
     * getRange()
     */
    double GlotzillaPotentialDzugutov::getRange() {
        return mPotential->GetCutoff();
    }

    /*
     * energy()
     */
    double GlotzillaPotentialDzugutov::energy(IAPIAtomList *as) {
printf("WARNING : GlotzillaPotentialDzugutov::energy() is NOT implemented.\n");
    }

    /*
     * getGlotzPotential()
     */
    glotzmd::Potential *GlotzillaPotentialDzugutov::getGlotzPotential() {
        return mPotential;
    }

}
