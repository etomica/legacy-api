/*
 *  LammpsAtomTypeSphere.cpp
 *  API Glue
 *
 */


#include "LammpsAtomTypeSphere.h"
#include "LammpsAtomType.h"

namespace lammpswrappers
{

    LammpsAtomTypeSphere::LammpsAtomTypeSphere() : LammpsAtomType() {
        diameter = 1.0;
    }

    LammpsAtomTypeSphere::LammpsAtomTypeSphere(double mass) : LammpsAtomType(mass) {
        diameter = 1.0;
    }

    LammpsAtomTypeSphere::LammpsAtomTypeSphere(int at) : LammpsAtomType(at) {
        diameter = 1.0;
    }

    LammpsAtomTypeSphere::LammpsAtomTypeSphere(int at, double mass) : LammpsAtomType(at, mass) {
        diameter = 1.0;
    }

    /*
     * setDiameter()
     */
    void LammpsAtomTypeSphere::setDiameter(double d) {
        diameter = d;
    }

    /*
     * getDiameter()
     */
    double LammpsAtomTypeSphere::getDiameter() {
        return diameter;
    }

}

