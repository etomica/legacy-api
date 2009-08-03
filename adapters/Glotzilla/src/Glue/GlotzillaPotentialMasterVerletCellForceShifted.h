/*
 *  GlotzillaPotentialMasterVerletCellForceShifted.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETCELLFORCESHIFT_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETCELLFORCESHIFT_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletCellForceShifted here.
      */
    class GlotzillaPotentialMasterVerletCellForceShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletCellForceShifted(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletCellForceShifted *mForce;

    };
}
#endif
