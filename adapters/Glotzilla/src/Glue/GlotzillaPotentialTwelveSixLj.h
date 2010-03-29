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
            /**
              * @param epsilon Epsilon value of potential
              */
            void setEpsilon(double epsilon);
            /**
              * @param sigma Sigma value of potential
              */
            void setSigma(double sigma);
            /**
              * @param cutoff Cutoff value of potential
              */
            void setCutoff(double cutoff);
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::TwelveSixLjPotential *mPotential;

    };
}
#endif
