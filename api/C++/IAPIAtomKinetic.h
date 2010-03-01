/*
 *  IAPIAtomKinetic.h
 *  API Glue
 *
 */

#ifndef API_IATOMKINETIC_WRAPPER_H
#define API_IATOMKINETIC_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIVectorMutable.h"

namespace molesimAPI
{

    class IAPIAtomKinetic : public virtual IAPIAtom {

        public:			
            virtual IAPIVectorMutable *getVelocity() = 0;

    };
}

#endif
