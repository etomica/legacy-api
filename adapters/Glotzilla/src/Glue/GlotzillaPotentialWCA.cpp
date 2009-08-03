/*
 *  GlotzillaPotentialWCA.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialWCA.h"

namespace glotzwrappers
{

    GlotzillaPotentialWCA::GlotzillaPotentialWCA() {
        mPotential = new glotzmd::WcaPotential;
    }

    /*
     * getRange()
     */
    double GlotzillaPotentialWCA::getRange() {
        mPotential->GetCutoff();
    }

    /*
     * energy()
     */
    double GlotzillaPotentialWCA::energy(IAPIAtomList *as) {
printf("WARNING : GlotzillaPotentialWCA::energy() is NOT implemented.\n");
    }

    /*
     * setSigma()
     */
    void GlotzillaPotentialWCA::setSigma(double sigma) {
        mPotential->SetSigma(sigma);
    }

    /*
     * setCutoff()
     */
    void GlotzillaPotentialWCA::setCutoff(double cutoff) {
        mPotential->SetCutoff(cutoff);
    }

    /*
     * getGlotzPotential()
     */
    glotzmd::Potential *GlotzillaPotentialWCA::getGlotzPotential() {
        return mPotential;
    }

}
