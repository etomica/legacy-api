/*
 *  LammpsBondQuartic.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsPotential.h"
#include "LammpsBondQuartic.h"

namespace lammpswrappers
{

    const char *const LammpsBondQuartic::BOND_NAME = "quartic";
    const int LammpsBondQuartic::K_INDEX  = 0;
    const int LammpsBondQuartic::B1_INDEX = 1;
    const int LammpsBondQuartic::B2_INDEX = 2;
    const int LammpsBondQuartic::RC_INDEX = 3;
    const int LammpsBondQuartic::U0_INDEX = 4;
    const int    LammpsBondQuartic::NPARMS = 5;
    const double LammpsBondQuartic::DEFAULT_K = 10000.0;
    const double LammpsBondQuartic::DEFAULT_B1 = 10000.0;
    const double LammpsBondQuartic::DEFAULT_B2 = 10000.0;
    const double LammpsBondQuartic::DEFAULT_RC = 1.0;
    const double LammpsBondQuartic::DEFAULT_U0 = 1.0;

    LammpsBondQuartic::LammpsBondQuartic(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, DEFAULT_K);
        setParameter(B1_INDEX, DEFAULT_B1);
        setParameter(B2_INDEX, DEFAULT_B2);
        setParameter(RC_INDEX, DEFAULT_RC);
        setParameter(U0_INDEX, DEFAULT_U0);
    }

    LammpsBondQuartic::LammpsBondQuartic(int n,
                                         double k,
                                         double b1,
                                         double b2,
                                         double rc,
                                         double u0) :
                                            LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, k);
        setParameter(B1_INDEX, b1);
        setParameter(B2_INDEX, b2);
        setParameter(RC_INDEX, rc);
        setParameter(U0_INDEX, u0);
    }

    /*
     * getRange()
     */
    double LammpsBondQuartic::getRange() {
        printf("WARNING : LammpsBondQuartic::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondQuartic::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondQuartic::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondQuartic::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondQuartic::setBox() is NOT implemented yet.\n");
    }

}

