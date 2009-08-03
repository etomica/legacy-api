/*
 *  GlotzillaVector.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaVector.h"

namespace glotzwrappers
{

    GlotzillaVector::GlotzillaVector() {
    }

    /*
     * getGlotzVector
     */
    glotzmath::glotz_vec *GlotzillaVector::getGlotzVector() {
        return glotzVec;
    }

}
