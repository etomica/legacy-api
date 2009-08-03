/*
 *  LammpsBondClass2.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPotential.h"
#include "LammpsBondClass2.h"

namespace lammpswrappers
{

    const char *const LammpsBondClass2::BOND_NAME = "class2";
    const int LammpsBondClass2::R0_INDEX = 0;
    const int LammpsBondClass2::K2_INDEX = 1;
    const int LammpsBondClass2::K3_INDEX = 2;
    const int LammpsBondClass2::K4_INDEX = 3;
    const int    LammpsBondClass2::NPARMS = 4;
    const double LammpsBondClass2::DEFAULT_R0 = 1.0;
    const double LammpsBondClass2::DEFAULT_K2 = 1.0;
    const double LammpsBondClass2::DEFAULT_K3 = 1.0;
    const double LammpsBondClass2::DEFAULT_K4 = 1.0;

    LammpsBondClass2::LammpsBondClass2(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(R0_INDEX, DEFAULT_R0);
        setParameter(K2_INDEX, DEFAULT_K2);
        setParameter(K3_INDEX, DEFAULT_K3);
        setParameter(K4_INDEX, DEFAULT_K4);
    }

    LammpsBondClass2::LammpsBondClass2(int n,
                                       double r0,
                                       double k2,
                                       double k3,
                                       double k4) :
                                         LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(R0_INDEX, r0);
        setParameter(K2_INDEX, k2);
        setParameter(K3_INDEX, k3);
        setParameter(K4_INDEX, k4);
    }

    /*
     * getRange()
     */
    double LammpsBondClass2::getRange() {
        printf("WARNING : LammpsBondClass2::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondClass2::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondClass2::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondClass2::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondClass2::setBox() is NOT implemented yet.\n");
    }

}

