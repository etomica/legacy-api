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
            virtual double getRange();
            virtual double energy(IAPIAtomList *);
            int nBody();
            void setBox(IAPIBox *box);

            // Non-API
            virtual void setup() = 0;
    };
}
#endif
