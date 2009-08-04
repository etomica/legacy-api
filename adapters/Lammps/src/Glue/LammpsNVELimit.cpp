/*
 *  LammpsNVELimit.cpp
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

#include "LammpsNVELimit.h"

namespace lammpswrappers
{

    LammpsNVELimit::LammpsNVELimit() : LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve/limit") + 1) * sizeof(char));
        strcpy(fixType, "nve/limit");
    }

}
