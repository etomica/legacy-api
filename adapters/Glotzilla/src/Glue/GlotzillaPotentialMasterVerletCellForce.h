/*
 *  GlotzillaPotentialMasterVerletCellForce.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETCELLFORCE_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETCELLFORCE_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletCellForce here.
      */
    class GlotzillaPotentialMasterVerletCellForce : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletCellForce(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletCellForce *mForce;

    };
}
#endif
