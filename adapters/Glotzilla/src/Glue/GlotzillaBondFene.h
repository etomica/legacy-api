/*
 *  GlotzillaBondFene.h
 *  API Glue
 *
 */

#ifndef GLOTZ_FENE_BOND_WRAPPER_H
#define GLOTZ_FENE_BOND_WRAPPER_H

#include "GlotzillaSpring.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBondFene is a class representing a Fene spring.
      * Its Glotzilla native counterpart is a glotzmd::FeneSpring but this
      * class does not hold an instance of its Glotzilla native counterpart
      * (See GlotzillaPotentialMaster).
      */
    class GlotzillaBondFene : public GlotzillaSpring {

        public:
            /**
              * Create an instance of a fene spring with default spring and
              * default extent (See GlotzillaSpring documentation for
              * default values).
              */
            GlotzillaBondFene();
            /**
              * Create an instance of a fene spring with the given spring and
              * given extent.
              * @param spring Spring property for the spring being created.
              * @param extent Extent property for the spring being created.
              */
            GlotzillaBondFene(double spring, double extent);

    };
}
#endif
