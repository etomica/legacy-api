/*
 *  GlotzillaRandom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaRandom.h"

namespace glotzwrappers
{

    GlotzillaRandom::GlotzillaRandom() {
        mRand = new glotzmath::StdLibErand48();
    }

    /*
     * nextDouble()
     */
    double GlotzillaRandom::nextDouble() {
        return mRand->GetUniformFloat();
    }

    /*
     * nextInt()
     */
    int GlotzillaRandom::nextInt(int maxInt) {
        return mRand->GetUniformInt(0, maxInt);
    }

    /*
     * nextGaussian()
     */
    double GlotzillaRandom::nextGaussian() {
        return mRand->GetGaussianFloat();
    }

}
