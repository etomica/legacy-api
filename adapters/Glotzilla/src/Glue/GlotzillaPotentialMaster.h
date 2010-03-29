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
#include "IAPISimulation.h"
#include "GlotzillaSimulation.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotentialMaster here.
      */
    class GlotzillaPotentialMaster {

        public:
            GlotzillaPotentialMaster(IAPISimulation *sim);

            // API Compliance
            /**
              * Add the given interaction between the given atom types.
              * Used for inter-molecule bonding.
              * @param potential The interaction
              * @param at1 First of the two atom types.
              * @param at2 Second of the two atom types.
              */
            void addPotential(IAPIPotentialAtomic *potential, IAPIAtomType *at1, IAPIAtomType *api2);

            // Non-API Method
            /**
              * Add the given interaction for atoms within a molecule of the
              * given species.  Used for intra-molecule bonding.
              * @param potential The interaction
              * @param species The species
              */
            void addPotential(IAPIPotential *potential, IAPISpecies *species);

            protected:
                GlotzillaSimulation *mSim;

    };
}
#endif
