/*
 *  LammpsSpace.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSpace.h"
#include "LammpsVector2D.h"
#include "LammpsVector3D.h"

namespace lammpssnifferwrappers
{

    LammpsSpace::LammpsSpace(int dim) {
        D = dim;
    }

    /*
     * getPosition()
     */
    int LammpsSpace::getD() {
        return D;
    }

    /*
     * makeVector()
     */
/*
    IAPIVectorMutable *LammpsSpace::makeVector() {

        IAPIVectorMutable *vec;

        if(D == 2) {
            vec = new LammpsVector2D();
        }
        else if(D == 3) {
            vec = new LammpsVector3D();
        }

        return vec;
    }
*/

    /*
     * makeVector()
     */
    IAPIVectorMutable *LammpsSpace::makeVector(double **vals) {

        IAPIVectorMutable *vec;

        if(D == 2) {
            vec = new LammpsVector2D(vals);
        }
        else if(D == 3) {
            vec = new LammpsVector3D(vals);
        }

        return vec;
    }

}
