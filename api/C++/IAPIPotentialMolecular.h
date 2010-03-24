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
            /**
             * Returns the interaction energy between the given molecules.
             * There might be 0, 1, 2 or more molecules in the molecule list.
             * @param moleList List containing the molecules to compute the
             *                 interaction.
             */
            virtual double energy(IAPIMoleculeList *moleList) = 0;
    };

}
#endif
