/*
 *  GlotzillaPotentialMasterVerletForce.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETFORCE_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETFORCE_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletForce here.
      */
    class GlotzillaPotentialMasterVerletForce : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletForce(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletForce *mForce;

    };
}
#endif
