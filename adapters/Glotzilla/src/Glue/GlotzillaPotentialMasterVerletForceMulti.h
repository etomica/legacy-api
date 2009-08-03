/*
 *  GlotzillaPotentialMasterVerletForceMulti.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETFORCEMULTI_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETFORCEMULTI_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletForceMulti here.
      */
    class GlotzillaPotentialMasterVerletForceMulti : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletForceMulti(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletForceMulti *mForce;

    };
}
#endif
