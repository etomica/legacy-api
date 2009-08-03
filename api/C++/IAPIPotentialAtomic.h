/*
 *  IAPIPotentialAtomic.h
 *  API Glue
 *
 */

#ifndef API_IPOTENTIAL_ATOMIC_WRAPPER_H
#define API_IPOTENTIAL_ATOMIC_WRAPPER_H

#include "IAPIAtomList.h"
#include "IAPIPotential.h"

namespace molesimAPI
{

    class IAPIPotentialAtomic : public virtual IAPIPotential {

        public:
          virtual double energy(IAPIAtomList *) = 0;
    };

}
#endif
