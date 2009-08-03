/*
 *  GlotzillaPotentialTwelveSixLj.h
 *  API Glue
 *
 */

#ifndef GLOTZ_126POTENTIAL_WRAPPER_H
#define GLOTZ_126POTENTIAL_WRAPPER_H

#include "IAPIAtomList.h"

#include "GlotzillaPotential.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialTwelveSixLj here.
      */
    class GlotzillaPotentialTwelveSixLj : public GlotzillaPotential {

        public:
            GlotzillaPotentialTwelveSixLj();

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *as);

            // Non-api Methods
            void setEpsilon(double epsilon);
            void setSigma(double sigma);
            void setCutoff(double cutoff);
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::TwelveSixLjPotential *mPotential;

    };
}
#endif
