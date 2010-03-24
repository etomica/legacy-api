/*
 *  GlotzillaPotential.h
 *  API Glue
 *
 *
 */

#ifndef GLOTZ_POTENTIAL_WRAPPER_H
#define GLOTZ_POTENTIAL_WRAPPER_H

#include <glotzmd.h>

#include "IAPIAtomList.h"
#include "IAPIBox.h"
#include "IAPIPotentialAtomic.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaPotential here.
      * The type of the Glotzilla native object is dependent on this instances
      * subclass.
      */
    class GlotzillaPotential : public virtual IAPIPotentialAtomic {

        public:

            // API Compliance
            virtual double getRange() = 0;
            virtual double energy(IAPIAtomList *) = 0;
            int nBody();
            void setBox(IAPIBox *box);

            // Non-API methods
           /**
             * WARNING : This method should not be called outside of the
             *           glue layer implementation.
             * @return Returns the Glotzilla native object
             *         (glotzmd::Potential) that this instance is holding.
             */
            virtual glotzmd::Potential *getGlotzPotential() = 0;

    };
}
#endif
