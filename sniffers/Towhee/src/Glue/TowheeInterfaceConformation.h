/*
 *  TowheeInterfaceConformation.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ICONFORMATION_WRAPPER_H
#define TOWHEE_ICONFORMATION_WRAPPER_H

#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeInterfaceConformation {

        public:
            virtual void initializePositions(IAPIAtomList *) = 0;
    };
}
#endif
