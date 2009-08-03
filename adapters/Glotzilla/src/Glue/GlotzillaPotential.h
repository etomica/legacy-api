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
            /**
              * @return Returns the range over which the potential applies.
              *         Atoms with a greater separation do not interact.
              */
            virtual double getRange() = 0;
            /**
              * @todo This method does not exist in IPotential.  So, either
              *       this method is going to disappear (moved to an
              *       appropriate subclass of IPotentialAtomic) OR this class
              *       will implement IPotentialAtomic).
              */
            virtual double energy(IAPIAtomList *) = 0;
            /**
              * @return Returns the number of atoms on which the potential
              *         depends.
              */
            int nBody();
            /**
              * Informs the potential of the box on which it acts so that it
              * can properly consider the boundaries.
              * @param box The box on which this potential acts.
              */
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
