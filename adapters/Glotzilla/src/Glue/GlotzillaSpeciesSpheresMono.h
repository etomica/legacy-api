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
              * Build a molecule of this species.  The molecule is an
              * instance of a GlotzillaMonatomicMolecule.
              * @return Returns the molecule constructed.
              */
            virtual IAPIMolecule *makeMolecule();
            /**
              * Add an atom type to the species atom type list used for
              * molecule creation.  Remove any atom type currently in the
              * list.
              * @param type atom type to add to list.
              */
            virtual void addChildType(IAPIAtomType *type);


        private:
            void init(IAPIAtomType *aType);
            IAPIAtomType *atomType;
    };
}

#endif
