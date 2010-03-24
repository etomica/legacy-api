/*
 *  TowheePotential.h
 *  API Glue
 *
 *
 */

#ifndef TOWHEE_POTENTIAL_WRAPPER_H
#define TOWHEE_POTENTIAL_WRAPPER_H

#include "IAPIAtomList.h"
#include "IAPIBox.h"
#include "IAPIPotentialAtomic.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheePotential : public virtual IAPIPotentialAtomic {

        public:

            // API Compliance
            /**
              * Determines the maximum distance after which atoms will not
              * interact by calling into the native Towhee simulation
              * (twh_max_bond_length).
              * @return Returns the number of atoms on which the potential
              *         depends.
              */
            virtual double getRange();
            /**
              * This method is not implemented.
              */
            virtual double energy(IAPIAtomList *atomList);
            int nBody();
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *box);

            // Non-API
            virtual void setup() = 0;
    };
}
#endif
