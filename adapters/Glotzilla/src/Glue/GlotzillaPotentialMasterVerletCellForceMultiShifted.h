/*
 *  GlotzillaPotentialMasterVerletCellForceMultiShifted.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VERLETCELLFORCEMULTISHIFT_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_VERLETCELLFORCEMULTISHIFT_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterVerletCellForceMultiShifted here.
      */
    class GlotzillaPotentialMasterVerletCellForceMultiShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterVerletCellForceMultiShifted(IAPISimulation *sim);

            // API Compliance

            // Non-API methods
            void setListUpdateFrequency(int freq);
            void setSkinThickness(double thick);

            private:
                glotzmd::VerletCellForceMultiShifted *mForce;

    };
}
#endif
