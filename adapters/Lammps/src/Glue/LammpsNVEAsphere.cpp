/*
 *  LammpsNVEAsphere.cpp
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

#include "LammpsNVEAsphere.h"

namespace lammpswrappers
{

    LammpsNVEAsphere::LammpsNVEAsphere() : LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve/asphere") + 1) * sizeof(char));
        strcpy(fixType, "nve/asphere");
    }

}
