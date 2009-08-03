/*
 *  GlotzillaBondHarmonic.h
 *  API Glue
 *
 */

#ifndef GLOTZ_HARMONIC_BOND_WRAPPER_H
#define GLOTZ_HARMONIC_BOND_WRAPPER_H

#include "GlotzillaSpring.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBondHarmonic is a class representing a Harmonic spring.
      * Its Glotzilla native counterpart is a glotzmd::HarmonicSpring but
      * this class does not hold an instance of its Glotzilla native
      * counterpart (See GlotzillaPotentialMaster).
      */
    class GlotzillaBondHarmonic : public GlotzillaSpring {

        public:
            /**
              * Create an instance of a harmonic spring with default spring
              * and default extent (See GlotzillaSpring documentation for
              * default values).
              */
            GlotzillaBondHarmonic();
            /**
              * Create an instance of a harmonic spring with the given spring
              * and given extent.
              * @param spring Spring property for the spring being created.
              * @param extent Extent property for the spring being created.
              */
            GlotzillaBondHarmonic(double spring, double extent);

    };
}
#endif
