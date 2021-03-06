/*
 *  LammpsNPTAsphere.cpp
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

#include "LammpsNPTAsphere.h"

namespace lammpswrappers
{

    LammpsNPTAsphere::LammpsNPTAsphere(double tStart, double tStop, double tDamp) :
                       LammpsNPT(tStart, tStop, tDamp) {
        fixType = (char *) malloc ((strlen("npt/asphere") + 1) * sizeof(char));
        strcpy(fixType, "npt/asphere");
    }

}
