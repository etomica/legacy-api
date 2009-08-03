/*
 *  LammpsNVENoforce.cpp
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

#include "LammpsNVENoforce.h"

namespace lammpswrappers
{

    LammpsNVENoforce::LammpsNVENoforce() : LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve/noforce") + 1) * sizeof(char));
        strcpy(fixType, "nve/noforce");
    }

}
