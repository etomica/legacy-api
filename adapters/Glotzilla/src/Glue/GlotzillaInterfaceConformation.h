/*
 *  GlotzillaInterfaceConformation.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ICONFORMATION_WRAPPER_H
#define GLOTZ_ICONFORMATION_WRAPPER_H

#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace glotzwrappers
{


    class GlotzillaInterfaceConformation {

        public:
            virtual void initializePositions(IAPIAtomList *) = 0;
    };
}
#endif
