/*
 *  LammpsNVENoforce.cpp
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

#include "LammpsNVENoforce.h"

namespace lammpswrappers
{

    LammpsNVENoforce::LammpsNVENoforce() : LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve/noforce") + 1) * sizeof(char));
        strcpy(fixType, "nve/noforce");
    }

}
