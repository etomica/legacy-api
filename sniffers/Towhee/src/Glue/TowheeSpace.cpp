/*
 *  TowheeSpace.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSpace.h"
#include "TowheeVector2D.h"
#include "TowheeVector3D.h"

namespace towheesnifferwrappers
{

    TowheeSpace::TowheeSpace(int dim) {
        D = dim;
    }

    /*
     * getPosition()
     */
    int TowheeSpace::getD() {
        return D;
    }

    /*
     * makeVector()
     */
    IAPIVectorMutable *TowheeSpace::makeVector() {

        IAPIVectorMutable *vec;

        if(D == 2) {
            vec = new TowheeVector2D();
        }
        else if(D == 3) {
            vec = new TowheeVector3D();
        }

        return vec;
    }

}
