/*
 *  LammpsBondFene.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsPotential.h"
#include "LammpsBondFene.h"

namespace lammpswrappers
{

    const char *const LammpsBondFene::BOND_NAME = "fene";
    const int LammpsBondFene::K_INDEX = 0;
    const int LammpsBondFene::R0_INDEX = 1;
    const int LammpsBondFene::EPSILON_INDEX = 2;
    const int LammpsBondFene::SIGMA_INDEX = 3;
    const int    LammpsBondFene::NPARMS = 4;
    const double LammpsBondFene::DEFAULT_K = 10000.0;
    const double LammpsBondFene::DEFAULT_R0 = 1.0;
    const double LammpsBondFene::DEFAULT_EPSILON = 1.0;
    const double LammpsBondFene::DEFAULT_SIGMA = 1.0;

    LammpsBondFene::LammpsBondFene(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, DEFAULT_K);
        setParameter(R0_INDEX, DEFAULT_R0);
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
    }

    LammpsBondFene::LammpsBondFene(int n,
                                   double k,
                                   double r0,
                                   double epsilon,
                                   double sigma) :
                                      LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, k);
        setParameter(R0_INDEX, r0);
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(SIGMA_INDEX, sigma);
    }

    /*
     * getRange()
     */
    double LammpsBondFene::getRange() {
        printf("WARNING : LammpsBondFene::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondFene::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondFene::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondFene::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondFene::setBox() is NOT implemented yet.\n");
    }

}

