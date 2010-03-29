/*
 *  GlotzillaSpeciesSpheresPolymer.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPECIESPOLY_WRAPPER_H
#define GLOTZ_SPECIESPOLY_WRAPPER_H

#include "IAPISimulation.h"
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
              * Build a molecule of this species.  The molecule is an
              * instance of a Glotzilla Polymer.
              * @return Returns the molecule constructed.
              */
            virtual IAPIMolecule *makeMolecule();

    };
}

#endif
