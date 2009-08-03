/*
 *  GlotzillaVerletForceShiftedPotentialMaster.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETFORCESHIFT_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETFORCESHIFT_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletForceShifted here.
      */
    class GlotzillaPotentialMasterVerletForceShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletForceShifted(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletForceShifted *mForce;

    };
}
#endif
