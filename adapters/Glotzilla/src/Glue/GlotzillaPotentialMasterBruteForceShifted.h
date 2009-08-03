/*
 *  GlotzillaPotentialMasterBruteForceShifted.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BRUTEFORCESHIFTED_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_BRUTEFORCESHIFTED_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterBruteForceShifted here.
      */
    class GlotzillaPotentialMasterBruteForceShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterBruteForceShifted(IAPISimulation *sim);

            // API Compliance

            private:
                glotzmd::BruteForceShifted *mBruteForce;

    };
}
#endif
