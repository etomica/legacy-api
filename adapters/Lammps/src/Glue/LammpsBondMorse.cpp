/*
 *  LammpsBondMorse.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPotential.h"
#include "LammpsBondMorse.h"

namespace lammpswrappers
{

    const char *const LammpsBondMorse::BOND_NAME = "morse";
    const int LammpsBondMorse::D_INDEX = 0;
    const int LammpsBondMorse::ALPHA_INDEX = 1;
    const int LammpsBondMorse::R0_INDEX = 2;
    const int    LammpsBondMorse::NPARMS = 3;
    const double LammpsBondMorse::DEFAULT_D = 1.0;
    const double LammpsBondMorse::DEFAULT_ALPHA = 1.0;
    const double LammpsBondMorse::DEFAULT_R0 = 1.0;

    LammpsBondMorse::LammpsBondMorse(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(D_INDEX, DEFAULT_D);
        setParameter(ALPHA_INDEX, DEFAULT_ALPHA);
        setParameter(R0_INDEX, DEFAULT_R0);
    }

    LammpsBondMorse::LammpsBondMorse(int n,
                                     double d,
                                     double alpha,
                                     double r0) :
                                         LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(D_INDEX, d);
        setParameter(ALPHA_INDEX, alpha);
        setParameter(R0_INDEX, r0);
    }

    /*
     * getRange()
     */
    double LammpsBondMorse::getRange() {
        printf("WARNING : LammpsBondMorse::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondMorse::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondMorse::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondMorse::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondMorse::setBox() is NOT implemented yet.\n");
    }

}

