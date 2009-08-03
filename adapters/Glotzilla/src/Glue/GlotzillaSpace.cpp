/*
 *  GlotzillaSpace.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSpace.h"
#include "GlotzillaVector2D.h"
#include "GlotzillaVector3D.h"

namespace glotzwrappers
{

    GlotzillaSpace::GlotzillaSpace(int dim) {
        D = dim;
    }

    /*
     * getPosition()
     */
    int GlotzillaSpace::getD() {
        return D;
    }

    /*
     * makeVector()
     */
    IAPIVectorMutable *GlotzillaSpace::makeVector() {

        IAPIVectorMutable *vec;

        if(D == 2) {
            vec = new GlotzillaVector2D();
        }
        else if(D == 3) {
            vec = new GlotzillaVector3D();
        }

        return vec;
    }

    /*
     * makeVector()
     */
    IAPIVectorMutable *GlotzillaSpace::makeVector(glotzmath::glotz_vec *gVec) {

        IAPIVectorMutable *vec;

        if(D == 2) {
            vec = new GlotzillaVector2D(gVec);
        }
        else if(D == 3) {
            vec = new GlotzillaVector3D(gVec);
        }

        return vec;
    }

}
