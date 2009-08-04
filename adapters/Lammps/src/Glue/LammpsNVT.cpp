/*
 *  LammpsNVT.cpp
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

#include "LammpsNVT.h"

namespace lammpswrappers
{

    LammpsNVT::LammpsNVT(double tStart, double tStop, double tDamp, double dragVal) {
        fixType = (char *) malloc ((strlen("nvt") + 1) * sizeof(char));
        strcpy(fixType, "nvt");
        start = tStart;
        stop = tStop;
        damp = tDamp;
        drag = dragVal;
        dofUsage = false;
    }

    LammpsNVT::LammpsNVT(double tStart, double tStop, double tDamp, double dragVal, int DOF) {
        fixType = (char *) malloc ((strlen("nvt") + 1) * sizeof(char));
        strcpy(fixType, "nvt");
        start = tStart;
        stop = tStop;
        damp = tDamp;
        drag = dragVal;
        dofUsage = true;
        dof = DOF;
    }

    /*
     * getStart
     */
    double LammpsNVT::getStart() {
        return start;
    }

    /*
     * getStop
     */
    double LammpsNVT::getStop() {
        return stop;
    }

    /*
     * getDamp
     */
    double LammpsNVT::getDamp() {
        return damp;
    }

    /*
     * getDrag
     */
    double LammpsNVT::getDrag() {
        return drag;
    }

    /*
     * useDOF
     */
    bool LammpsNVT::useDOF() {
        return dofUsage;
    }

    /*
     * getDOF
     */
    int LammpsNVT::getDOF() {
        return dof;
    }

    /*
     * getFixType
     */
    char *LammpsNVT::getFixType() {
        return fixType;
    }


}
