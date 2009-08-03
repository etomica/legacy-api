/*
 *  LammpsNVE.cpp
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

#include "LammpsNVE.h"

namespace lammpswrappers
{

    LammpsNVE::LammpsNVE() {
        fixType = (char *) malloc ((strlen("nve") + 1) * sizeof(char));
        strcpy(fixType, "nve");
    }

    /*
     * getFixType()
     */
    char *LammpsNVE::getFixType() {
        return fixType;
    }

}
