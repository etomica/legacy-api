/*
 *  TowheeInterfaceAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef TOWHEE_IATOMPOSITIONDEF_WRAPPER_H
#define TOWHEE_IATOMPOSITIONDEF_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIMolecule.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeInterfaceAtomPositionDefinition {

        public:
            virtual IAPIVector *position(IAPIMolecule *atom) = 0;
    };
}
#endif
