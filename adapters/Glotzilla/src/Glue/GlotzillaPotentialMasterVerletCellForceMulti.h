/*
 *  GlotzillaPotentialMasterVerletCellForceMulti.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETCELLFORCEMULTI_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETCELLFORCEMULTI_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletCellForceMulti here.
      */
    class GlotzillaPotentialMasterVerletCellForceMulti : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletCellForceMulti(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletCellForceMulti *mForce;

    };
}
#endif
