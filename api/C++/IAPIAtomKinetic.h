/*
 *  IAPIAtomKinetic.h
 *  API Glue
 *
 */

#ifndef API_IATOMKINETIC_WRAPPER_H
#define API_IATOMKINETIC_WRAPPER_H

#include "IAPIAtomPositioned.h"
#include "IAPIVectorMutable.h"

namespace molesimAPI
{

    class IAPIAtomKinetic : public virtual IAPIAtomPositioned {

        public:			
            virtual IAPIVectorMutable *getVelocity() = 0;

    };
}

#endif
