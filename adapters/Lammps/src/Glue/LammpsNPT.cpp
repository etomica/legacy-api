/*
 *  LammpsNPT.cpp
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

#include "LammpsNPT.h"

namespace lammpswrappers
{

    LammpsNPT::LammpsNPT(double tStart, double tStop, double tDamp) {
        fixType = (char *) malloc ((strlen("npt") + 1) * sizeof(char));
        strcpy(fixType, "npt");
        start = tStart;
        stop = tStop;
        damp = tDamp;
    }

    /*
     * getStart()
     */
    double LammpsNPT::getStart() {
        return start;
    }

    /*
     * getStop()
     */
    double LammpsNPT::getStop() {
        return stop;
    }

    /*
     * getDamp()
     */
    double LammpsNPT::getDamp() {
        return damp;
    }

    /*
     * getFixType()
     */
    char *LammpsNPT::getFixType() {
        return fixType;
    }

}
