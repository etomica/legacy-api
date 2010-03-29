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
            /**
              * @param power Power value of potential
              */
            void setPower(double power);
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::GeneralLjPotential *mPotential;

    };
}
#endif
