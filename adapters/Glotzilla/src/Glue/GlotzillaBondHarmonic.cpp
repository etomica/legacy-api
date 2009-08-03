/*
 *  GlotzillaBondHarmonic.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaBondHarmonic.h"

namespace glotzwrappers
{

    GlotzillaBondHarmonic::GlotzillaBondHarmonic() : GlotzillaSpring() {
    }

    GlotzillaBondHarmonic::GlotzillaBondHarmonic(double spring, double extent) :
                                                GlotzillaSpring(spring, extent) {
    }

}
