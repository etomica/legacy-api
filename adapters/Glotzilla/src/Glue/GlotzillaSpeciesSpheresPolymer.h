/*
 *  GlotzillaSpeciesSpheresPolymer.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPECIESPOLY_WRAPPER_H
#define GLOTZ_SPECIESPOLY_WRAPPER_H

#include "IAPISimulation.h"
#include "IAPISpeciesManager.h"
#include "GlotzillaInterfaceConformation.h"
#include "GlotzillaSpecies.h"
#include "GlotzillaAtomTypeSphere.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * Species in which polymers are made of a one or more spherical
      * atoms. This species creates polymers of type GlotzillaPolymer.
      */
    class GlotzillaSpeciesSpheresPolymer : public GlotzillaSpecies {

        public:
            /**
              * @todo Document this constructor.
              */
            GlotzillaSpeciesSpheresPolymer(IAPISimulation *sim);
            /**
              * @todo Document this constructor.
              */
            GlotzillaSpeciesSpheresPolymer(IAPISimulation *sim,
                                           GlotzillaInterfaceConformation *conf);

            // API compliant methods
            /**
              * Build a molecule of this species.
              * @return Returns the molecule constructed.
              * @todo Describe, in more detail, how a molecule of this
              *       species is made.
              */
            virtual IAPIMolecule *makeMolecule();

    };
}

#endif