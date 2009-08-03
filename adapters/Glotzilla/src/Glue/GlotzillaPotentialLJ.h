/*
 *  GlotzillaPotentialLJ.h
 *  API Glue
 *
 */

#ifndef GLOTZ_LJPOTENTIAL_WRAPPER_H
#define GLOTZ_LJPOTENTIAL_WRAPPER_H

#include "IAPIAtomList.h"

#include "GlotzillaPotential.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialLJ here.
      */
    class GlotzillaPotentialLJ : public GlotzillaPotential {

        public:
            GlotzillaPotentialLJ();

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *as);

            // Non-api Methods
            void setEpsilon(double epsilon);
            void setSigma(double sigma);
            void setCutoff(double cutoff);
            void setPower(double power);
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::GeneralLjPotential *mPotential;

    };
}
#endif
