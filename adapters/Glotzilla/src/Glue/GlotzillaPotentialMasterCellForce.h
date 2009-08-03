/*
 *  GlotzillaPotentialMasterCellForce.h
 *  API Glue
 *
 */

#ifndef GLOTZ_CELLFORCE_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_CELLFORCE_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterCellForce here.
      */
    class GlotzillaPotentialMasterCellForce : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterCellForce(IAPISimulation *sim);

            // API Compliance

            private:
                glotzmd::CellForce *mForce;

    };
}
#endif
