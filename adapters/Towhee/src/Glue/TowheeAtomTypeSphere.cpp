/*
 *  TowheeAtomTypeSphere.cpp
 *  API Glue
 *
 */

#include "TowheeAtomTypeSphere.h"
#include "TowheeAtomType.h"

namespace towheewrappers
{

    TowheeAtomTypeSphere::TowheeAtomTypeSphere(int index) : TowheeAtomType(index) {
    }

    /*
     * setDiameter()
     */
    void TowheeAtomTypeSphere::setDiameter(double d) {
        mDiameter = d;
    }

    /*
     * getDiameter()
     */
    double TowheeAtomTypeSphere::getDiameter() {
        return mDiameter;
    }

}

