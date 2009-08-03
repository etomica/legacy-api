/*
 *  GlotzillaSpeciesSpheresMono.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPECIESMONO_WRAPPER_H
#define GLOTZ_SPECIESMONO_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "IAPISimulation.h"
#include "IAPISpeciesManager.h"
#include "GlotzillaInterfaceConformation.h"
#include "GlotzillaSpecies.h"
#include "GlotzillaAtomTypeSphere.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * Species in which molecules are made of a single spherical atom. This
      * species creates molecules of type GlotzillaMonatomicMolecule.
      */
    class GlotzillaSpeciesSpheresMono : public GlotzillaSpecies {

        public:
            /**
              * @todo Document this constructor.
              */
            GlotzillaSpeciesSpheresMono(IAPISimulation *sim,
                                        IAPIAtomType *aType);
            /**
              * @todo Document this constructor.
              */
            GlotzillaSpeciesSpheresMono(IAPISimulation *sim,
                                        IAPIAtomType *aType,
                                        GlotzillaInterfaceConformation *conf);

            // API compliant methods
            /**
              * Build a molecule of this species.
              * @return Returns the molecule constructed.
              * @todo Describe, in more detail, how a molecule of this
              *       species is made.
              */
            virtual IAPIMolecule *makeMolecule();
            virtual void addChildType(IAPIAtomType *type);


        private:
            void init(IAPIAtomType *aType);
            IAPIAtomType *atomType;
    };
}

#endif
