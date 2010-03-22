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
            /**
              * @return Returns a vector holding the velocity of the atom.
              *         The velocity of the atom can be changed by changing
              *         the values of the returned vector.
              */
            virtual IAPIVectorMutable *getVelocity() = 0;

    };
}

#endif
