/*
 *  TowheeAtomTypeSphere.cpp
 *  API Glue
 *
 */

#include "TowheeAtomTypeSphere.h"
#include "TowheeAtomType.h"

namespace towheesnifferwrappers
{

    TowheeAtomTypeSphere::TowheeAtomTypeSphere(int index) : TowheeAtomType(index) {
    }

    /*
     * setDiameter()
     *   NOTE : The method can be impleted as the diameter is not passed
     *          to the Towhee simulation.
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

