/*
 *  GlotzillaPotentialMasterBruteForce.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BRUTEFORCE_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_BRUTEFORCE_POTENTIALMASTER_WRAPPER_H

#include <glotzmd.h>

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterBruteForce here.
      */
    class GlotzillaPotentialMasterBruteForce :
                                  public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterBruteForce(IAPISimulation *sim);

            // API Compliance

            private:
                glotzmd::BruteForce *mBruteForce;

    };
}
#endif
