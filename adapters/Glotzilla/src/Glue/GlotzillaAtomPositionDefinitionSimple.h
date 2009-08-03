/*
 *  GlotzillaAtomPositionDefinitionSimple.h.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOMTYPEPOSDEFSIMPLE_WRAPPER_H
#define GLOTZ_ATOMTYPEPOSDEFSIMPLE_WRAPPER_H

#include "GlotzillaInterfaceAtomPositionDefinition.h"
#include "IAPIMolecule.h"
#include "IAPIVector.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtomPositionDefinitionSimple determines a molecules's
      * position as the position of the first atom held in its child list.
      */
    class GlotzillaAtomPositionDefinitionSimple : public virtual GlotzillaInterfaceAtomPositionDefinition {

        public:
            /**
              * Create a GlotzillaAtomPositionDefinitionSimple.
              */
            GlotzillaAtomPositionDefinitionSimple() {};

            // API Compliance
            /**
              * The molecule's position is determined as the position of the
              * first atom in the molecule's child list.
              * @return Returns the molecule's position as described.
              */
            IAPIVector *position(IAPIMolecule *atom);

    };
}
#endif
