/*
 *  LammpsBondNonlinear.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsPotential.h"
#include "LammpsBondNonlinear.h"

namespace lammpswrappers
{

    const char *const LammpsBondNonlinear::BOND_NAME = BOND_NAME;
    const int LammpsBondNonlinear::EPSILON_INDEX = 0;
    const int LammpsBondNonlinear::R0_INDEX = 1;
    const int LammpsBondNonlinear::LAMBDA_INDEX = 2;
    const int    LammpsBondNonlinear::NPARMS = 3;
    const double LammpsBondNonlinear::DEFAULT_EPSILON = 100.0;
    const double LammpsBondNonlinear::DEFAULT_R0 = 1.0;
    const double LammpsBondNonlinear::DEFAULT_LAMBDA = 1.5;

    LammpsBondNonlinear::LammpsBondNonlinear(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(R0_INDEX, DEFAULT_R0);
        setParameter(LAMBDA_INDEX, DEFAULT_LAMBDA);
    }

    LammpsBondNonlinear::LammpsBondNonlinear(int n,
                                             double epsilon,
                                             double r0,
                                             double lambda) :
                                                LammpsPotential(n, NPARMS, "nonlinear") {
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(R0_INDEX, r0);
        setParameter(LAMBDA_INDEX, lambda);
    }

    /*
     * getRange()
     */
    double LammpsBondNonlinear::getRange() {
        printf("WARNING : LammpsBondNonlinear::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondNonlinear::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondNonlinear::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondNonlinear::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondNonlinear::setBox() is NOT implemented yet.\n");
    }

}

