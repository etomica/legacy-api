/*
 *  GlotzillaPotentialMasterCellForceMulti.h
 *  API Glue
 *
 */

#ifndef GLOTZ_CELLFORCEMULTI_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_CELLFORCEMULTI_POTENTIALMASTER_WRAPPER_H

#include "IAPISimulation.h"
#include "GlotzillaPotentialMaster.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMasterCellForceMulti here.
      */
    class GlotzillaPotentialMasterCellForceMulti : public GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMasterCellForceMulti(IAPISimulation *sim);

            // API Compliance

            private:
                glotzmd::CellForceMulti *mForce;

    };
}
#endif
