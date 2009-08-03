/*
 *  GlotzillaBondFene.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaBondFene.h"

namespace glotzwrappers
{

    GlotzillaBondFene::GlotzillaBondFene() : GlotzillaSpring() {
    }

    GlotzillaBondFene::GlotzillaBondFene(double spring, double extent) :
                                            GlotzillaSpring(spring, extent) {
    }

}
