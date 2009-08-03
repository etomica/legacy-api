/*
 *  LammpsNVESphere.cpp
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

#include "LammpsNVESphere.h"

namespace lammpswrappers
{

    LammpsNVESphere::LammpsNVESphere() : LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve/sphere") + 1) * sizeof(char));
        strcpy(fixType, "nve/sphere");
    }

}
