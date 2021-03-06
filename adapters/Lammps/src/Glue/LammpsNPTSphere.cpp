/*
 *  LammpsNPTSphere.cpp
 *  API Glue
 *
 */

#include "string.h"

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "library.h"

#include "LammpsNPTSphere.h"

namespace lammpswrappers
{

    LammpsNPTSphere::LammpsNPTSphere(double tStart, double tStop, double tDamp) :
                       LammpsNPT(tStart, tStop, tDamp) {
        fixType = (char *) malloc ((strlen("npt/Sphere") + 1) * sizeof(char));
        strcpy(fixType, "npt/Sphere");
    }

}
