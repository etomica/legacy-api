/*
 *  GlotzillaPotentialWCA.h
 *  API Glue
 *
 */

#ifndef GLOTZ_WCAPOTENTIAL_WRAPPER_H
#define GLOTZ_WCAPOTENTIAL_WRAPPER_H

#include "IAPIAtomList.h"

#include "GlotzillaPotential.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialWCA here.
      */
    class GlotzillaPotentialWCA : public GlotzillaPotential {

        public:
            GlotzillaPotentialWCA();

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *as);

            // Non-api Methods
            void setSigma(double sigma);
            void setCutoff(double cutoff);
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::WcaPotential *mPotential;

    };
}
#endif
