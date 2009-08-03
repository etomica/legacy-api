/*
 *  GlotzillaPotentialMasterCellForceShifted.h
 *  API Glue
 *
 */

#ifndef GLOTZ_CELLFORCESHIFTED_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_CELLFORCESHIFTED_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterCellForceShifted here.
      */
    class GlotzillaPotentialMasterCellForceShifted : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterCellForceShifted(IAPISimulation *sim);

            // API Compliance

            private:
                glotzmd::CellForceShifted *mForce;

    };
}
#endif
