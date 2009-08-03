/*
 *  LammpsMomentum.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsMomentum.h"

namespace lammpswrappers
{

    const int LammpsMomentum::LINEAR = 0;
    const int LammpsMomentum::ANGULAR = 1;

    LammpsMomentum::LammpsMomentum(int steps, int type) {
        enabled = true;
        momentumSteps = steps;
        momentumType = type;
        xflag = true;
        yflag = true;
        zflag = true;
    }

    /*
     * setState
     */
    void LammpsMomentum::setState(bool state) {
        enabled = state;
    }

    /*
     * getState
     */
    bool LammpsMomentum::getState() {
        return enabled;
    }

    /*
     * setLinearFlags
     */
    void LammpsMomentum::setLinearFlags(int x, int y, int z) {
        xflag = x;
        yflag = y;
        zflag = z;
    }

    /*
     * getXLinearFlag
     */
    int LammpsMomentum::getXLinearFlag() {
        return xflag;
    }

    /*
     * getYLinearFlag
     */
    int LammpsMomentum::getYLinearFlag() {
        return yflag;
    }

    /*
     * getZLinearFlag
     */
    int LammpsMomentum::getZLinearFlag() {
        return zflag;
    }

    /*
     * getSteps
     */
    int LammpsMomentum::getSteps() {
        return momentumSteps;
    }

    /*
     * getType
     */
    int LammpsMomentum::getType() {
        return momentumType;
    }

}
