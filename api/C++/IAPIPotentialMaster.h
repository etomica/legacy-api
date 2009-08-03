/*
 *  IAPIPotentialMaster.h
 *  API Glue
 *
 */

#ifndef API_IPOTENTIALMASTER_WRAPPER_H
#define API_IPOTENTIALMASTER_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIPotentialAtomic.h"

namespace molesimAPI
{

    class IAPIPotentialMaster {

        public:

            // Non-api methods
            virtual void addPotential(IAPIPotentialAtomic *, IAPIAtomType *, IAPIAtomType *) = 0;

    };
}
#endif
