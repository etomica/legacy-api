/*
 *  GlotzillaPotentialMaster.h
 *  API Glue
 *
 *
 */

#ifndef GLOTZ_POTENTIALMASTER_WRAPPER_H
#define GLOTZ_POTENTIALMASTER_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIPotential.h"
#include "IAPIPotentialAtomic.h"
#include "IAPIPotentialMaster.h"
#include "IAPISimulation.h"
#include "GlotzillaSimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMaster here.
      */
    class GlotzillaPotentialMaster : public virtual IAPIPotentialMaster {

        public:
            GlotzillaPotentialMaster(IAPISimulation *sim);

            // API Compliance
            void addPotential(IAPIPotentialAtomic *potential, IAPIAtomType *at1, IAPIAtomType *api2);

            // Non-API Method
            // The next method is very close to the API method :
            //  addPotential(IPotential, ISpecies[]);
            void addPotential(IAPIPotential *potential, IAPISpecies *species);

            protected:
                GlotzillaSimulation *mSim;

    };
}
#endif
