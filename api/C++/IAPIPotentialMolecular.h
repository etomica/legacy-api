/*
 *  IAPIPotentialMolecular.h
 *  API Glue
 *
 */

#ifndef API_IPOTENTIAL_MOLECULAR_WRAPPER_H
#define API_IPOTENTIAL_MOLECULAR_WRAPPER_H

#include "IAPIMoleculeList.h"
#include "IAPIPotential.h"

namespace molesimAPI
{

    class IAPIPotentialMolecular : public virtual IAPIPotential {

        public:
          virtual double energy(IAPIMoleculeList *) = 0;
    };

}
#endif
