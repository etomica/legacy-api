/*
 *  GlotzillaPotentialLJ.cpp
 *  API Glue
 *
 *
 */

#include <glotzmd.h>

#include "GlotzillaPotentialLJ.h"

namespace glotzwrappers
{

    GlotzillaPotentialLJ::GlotzillaPotentialLJ() {
        mPotential = new glotzmd::GeneralLjPotential;
    }

    /*
     * getRange()
     */
    double GlotzillaPotentialLJ::getRange() {
        mPotential->GetCutoff();
    }

    /*
     * energy()
     */
    double GlotzillaPotentialLJ::energy(IAPIAtomList *as) {
printf("WARNING : GlotzillaPotentialLJ::energy() is NOT implemented.\n");
    }

    /*
     * setEpsilon()
     */
    void GlotzillaPotentialLJ::setEpsilon(double epsilon) {
        mPotential->SetEpsilon(epsilon);
    }

    /*
     * setSigma()
     */
    void GlotzillaPotentialLJ::setSigma(double sigma) {
        mPotential->SetSigma(sigma);
    }

    /*
     * setCutoff()
     */
    void GlotzillaPotentialLJ::setCutoff(double cutoff) {
        mPotential->SetCutoff(cutoff);
    }

    /*
     * setPower()
     */
    void GlotzillaPotentialLJ::setPower(double power) {
        mPotential->SetPower(power);
    }

    /*
     * getGlotzPotential()
     */
    glotzmd::Potential *GlotzillaPotentialLJ::getGlotzPotential() {
        return mPotential;
    }

}
