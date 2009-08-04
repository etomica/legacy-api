/*
 *  LammpsNVTSphere.cpp
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

#include "LammpsNVTSphere.h"

namespace lammpswrappers
{

    LammpsNVTSphere::LammpsNVTSphere(double tStart, double tStop, double tDamp, double dragVal) :
          LammpsNVT(tStart, tStop, tDamp, dragVal) {
        fixType = (char *) malloc ((strlen("nvt/sphere") + 1) * sizeof(char));
        strcpy(fixType, "nvt/sphere");
    }

}
