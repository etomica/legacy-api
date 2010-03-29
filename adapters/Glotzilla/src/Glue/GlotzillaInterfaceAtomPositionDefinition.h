/*
 *  GlotzillaInterfaceAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef GLOTZ_IATOMPOSITIONDEF_WRAPPER_H
#define GLOTZ_IATOMPOSITIONDEF_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIMolecule.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    class GlotzillaInterfaceAtomPositionDefinition {

        public:
            /**
              * A method that determines and returns the position of a
              * molecule.
              * @param atom The molecule to determine the position of.
              * @return Returns the molecule's position.
              */
            virtual IAPIVector *position(IAPIMolecule *atom) = 0;
    };
}
#endif
