/*
 *  LammpsNVTAsphere.cpp
 *  API Glue
 *
 */

#include "string.h"

#ifdef __MACOSX__
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "library.h"

#include "LammpsNVTAsphere.h"

namespace lammpswrappers
{

    LammpsNVTAsphere::LammpsNVTAsphere(double tStart, double tStop, double tDamp, double dragVal) :
          LammpsNVT(tStart, tStop, tDamp, dragVal) {
        fixType = (char *) malloc ((strlen("nvt/asphere") + 1) * sizeof(char));
        strcpy(fixType, "nvt/asphere");
    }

}
