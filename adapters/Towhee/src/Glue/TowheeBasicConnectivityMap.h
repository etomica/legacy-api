/*
 *  TowheeBasicConnectivityMap.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BASIC_CONNECTIVITY_MAP_WRAPPER_H
#define TOWHEE_BASIC_CONNECTIVITY_MAP_WRAPPER_H

#include "IAPIMolecule.h"
#include "TowheeForceField.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeBasicConnectivityMap {

        public:
            TowheeBasicConnectivityMap();

            void setup(IAPIMolecule *molecule, TowheeForceField *ff);

    };
}
#endif
