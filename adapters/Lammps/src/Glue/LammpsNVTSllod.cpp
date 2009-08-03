/*
 *  LammpsNVTSllod.cpp
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

#include "LammpsNVTSllod.h"

namespace lammpswrappers
{

    LammpsNVTSllod::LammpsNVTSllod(double tStart, double tStop, double tDamp, double dragVal) :
          LammpsNVT(tStart, tStop, tDamp, dragVal) {
        fixType = (char *) malloc ((strlen("nvt/sllod") + 1) * sizeof(char));
        strcpy(fixType, "nvt/sllod");
    }

}
