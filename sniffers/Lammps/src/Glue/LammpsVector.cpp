/*
 *  LammpsVector.cpp
 *  API Glue
 *
 */

#include "LammpsVector.h"

namespace lammpssnifferwrappers
{

    LammpsVector::LammpsVector() {
    }

    double **LammpsVector::getLammpsVector() {
        return pos;
    }


}
