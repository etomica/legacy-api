/*
 *  GlotzillaPotentialMasterVerletForceMultiShifted.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETFORCEMULTISHIFT_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETFORCEMULTISHIFT_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletForceMultiShifted here.
      */
    class GlotzillaPotentialMasterVerletForceMultiShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletForceMultiShifted(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletForceMultiShifted *mForce;

    };
}
#endif
