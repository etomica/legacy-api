/*
 *  TowheePotential.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include "preproc.h"

#include "TowheePotential.h"

extern "C" { void twh_max_bond_length_(int *, double *); }

namespace towheewrappers
{

    /*
     * getRange()
     */
    double TowheePotential::getRange() {
        int get = GLB_GET;
        double bondLength;
        twh_max_bond_length_(&get, &bondLength);

        return bondLength;
    }

    /*
     * energy()
     */
    double TowheePotential::energy(IAPIAtomList *atomList) {
    }

    /*
     * nBody()
     */
    int TowheePotential::nBody() {
printf("WARNING : TowheePotential::nBody() is NOT implemented.\n");
        return 2;
    }

    /*
     * setBox()
     */
    void TowheePotential::setBox(IAPIBox *box) {
printf("WARNING : TowheePotential::setBox() is NOT implemented.\n");
    }

}
