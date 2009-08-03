/*
 *  LammpsMethodNotImplementedException.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsMethodNotImplementedException.h"

namespace lammpswrappers
{

    LammpsMethodNotImplementedException::LammpsMethodNotImplementedException(char *msg) {
        mMessage = msg;
    }

    /*
     * what()
     */
    const char *LammpsMethodNotImplementedException::what() const throw() {
        return mMessage;
    }

}
