/*
 *  LammpsVector.cpp
 *  API Glue
 *
 */

#include "LammpsVector.h"

namespace lammpswrappers
{

    LammpsVector::LammpsVector() {
    }

    double *LammpsVector::getLammpsVector() {
        return pos;
    }


}
