/*
 *  GlotzillaAtomTypeSphere.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaAtomTypeSphere.h"
#include "GlotzillaAtomType.h"

namespace glotzwrappers
{

    GlotzillaAtomTypeSphere::GlotzillaAtomTypeSphere() : GlotzillaAtomType() {
        diameter = 0.0;
    }

    GlotzillaAtomTypeSphere::GlotzillaAtomTypeSphere(int at) : GlotzillaAtomType(at) {
        diameter = 0.0;
    }

    GlotzillaAtomTypeSphere::GlotzillaAtomTypeSphere(int at, double mass) : GlotzillaAtomType(at, mass) {
        diameter = 0.0;
    }

    /*
     * setDiameter()
     */
    void GlotzillaAtomTypeSphere::setDiameter(double d) {
        diameter = d;
    }

    /*
     * getDiameter()
     */
    double GlotzillaAtomTypeSphere::getDiameter() {
        return diameter;
    }

}

