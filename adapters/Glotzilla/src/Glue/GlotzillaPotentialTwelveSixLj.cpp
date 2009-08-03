/*
 *  GlotzillaPotentialTwelveSixLj.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialTwelveSixLj.h"

namespace glotzwrappers
{

    GlotzillaPotentialTwelveSixLj::GlotzillaPotentialTwelveSixLj() {
        mPotential = new glotzmd::TwelveSixLjPotential;
    }

    /*
     * getRange()
     */
    double GlotzillaPotentialTwelveSixLj::getRange() {
        mPotential->GetCutoff();
    }

    /*
     * energy()
     */
    double GlotzillaPotentialTwelveSixLj::energy(IAPIAtomList *as) {
printf("WARNING : GlotzillaPotentialTwelveSixLj::energy() is NOT implemented.\n");
    }

    /*
     * setEpsilon()
     */
    void GlotzillaPotentialTwelveSixLj::setEpsilon(double epsilon) {
        mPotential->SetEpsilon(epsilon);
    }

    /*
     * setSigma()
     */
    void GlotzillaPotentialTwelveSixLj::setSigma(double sigma) {
        mPotential->SetSigma(sigma);
    }

    /*
     * setCutoff()
     */
    void GlotzillaPotentialTwelveSixLj::setCutoff(double cutoff) {
        mPotential->SetCutoff(cutoff);
    }

    /*
     * getGlotzPotential()
     */
    glotzmd::Potential *GlotzillaPotentialTwelveSixLj::getGlotzPotential() {
        return mPotential;
    }

}
