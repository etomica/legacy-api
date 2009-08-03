/*
 *  LammpsNPH.cpp
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

#include "LammpsNPH.h"

namespace lammpswrappers
{

    LammpsNPH::LammpsNPH() {
        fixType = (char *) malloc ((strlen("nph") + 1) * sizeof(char));
        strcpy(fixType, "nph");
    }

    /*
     * getFixType()
     */
    char *LammpsNPH::getFixType() {
        return fixType;
    }

}
