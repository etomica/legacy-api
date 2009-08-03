/*
 *  IAPIAtomPositioned.h
 *  API Glue
 *
 */

#ifndef API_IATOMPOS_WRAPPER_H
#define API_IATOMPOS_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIVectorMutable.h"

namespace molesimAPI
{

    class IAPIAtomPositioned : public virtual IAPIAtom {

        public:			
            virtual IAPIVectorMutable *getPosition() = 0;

    };
}

#endif
