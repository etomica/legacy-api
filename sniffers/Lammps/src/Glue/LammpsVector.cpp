/*
 *  LammpsVector.cpp
 *  API Glue
 *
 */
#include "stdio.h"
#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "LammpsVector.h"

namespace lammpssnifferwrappers
{

    LammpsVector::LammpsVector() {
    }

    LammpsVector::~LammpsVector() {
        free(pos[0][0]);
        free(pos[0]);
        free(pos);
    }

    double ***LammpsVector::getLammpsVector() {
        return pos;
    }


}
