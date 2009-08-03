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
            virtual IAPIVector *position(IAPIMolecule *atom) = 0;
    };
}
#endif
