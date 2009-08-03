/*
 *  GlotzillaPotentialDzugutov.h
 *  API Glue
 *
 */

#ifndef GLOTZ_DZUGUTOVPOTENTIAL_WRAPPER_H
#define GLOTZ_DZUGUTOVPOTENTIAL_WRAPPER_H

#include "IAPIAtomList.h"

#include "GlotzillaPotential.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialDzugutov here.
      */
    class GlotzillaPotentialDzugutov : public GlotzillaPotential {

        public:
            GlotzillaPotentialDzugutov();

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *as);

            // Non-api Methods
            glotzmd::Potential *getGlotzPotential();

        private:
            glotzmd::DzugutovPotential *mPotential;

    };
}
#endif
