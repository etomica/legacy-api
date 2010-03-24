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
            /**
             * Returns the interaction energy between the given atoms.
             * There might be 0, 1, 2 or more atoms in the atom list.
             * @param atomList List containing the atoms to compute the
             *                 interaction.
             */
            virtual double energy(IAPIAtomList *atomList) = 0;
    };

}
#endif
