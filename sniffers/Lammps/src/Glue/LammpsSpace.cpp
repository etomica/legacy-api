/*
 *  LammpsSpace.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

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
    IAPIVectorMutable *LammpsSpace::makeVector() {

        IAPIVectorMutable *vec;

        double **vals;
        vals = (double **) malloc (D * sizeof(double *));
        for(int i = 0; i < D; i++)
            vals[i] = (double *) malloc (1 * sizeof(double));

        if(D == 2) {
            vec = new LammpsVector2D(vals);
        }
        else if(D == 3) {
            vec = new LammpsVector3D(vals);
        }

        return vec;
    }

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
