/*
 *  LammpsBondFeneExpand.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsPotential.h"
#include "LammpsBondFeneExpand.h"

namespace lammpswrappers
{

    const char *const LammpsBondFeneExpand::BOND_NAME = "fene/expand";
    const int LammpsBondFeneExpand::K_INDEX = 0;
    const int LammpsBondFeneExpand::R0_INDEX = 1;
    const int LammpsBondFeneExpand::EPSILON_INDEX = 2;
    const int LammpsBondFeneExpand::SIGMA_INDEX = 3;
    const int LammpsBondFeneExpand::DELTA_INDEX = 4;
    const int    LammpsBondFeneExpand::NPARMS = 5;
    const double LammpsBondFeneExpand::DEFAULT_K = 10000.0;
    const double LammpsBondFeneExpand::DEFAULT_R0 = 1.0;
    const double LammpsBondFeneExpand::DEFAULT_EPSILON = 1.0;
    const double LammpsBondFeneExpand::DEFAULT_SIGMA = 1.0;
    const double LammpsBondFeneExpand::DEFAULT_DELTA = 1.0;

    LammpsBondFeneExpand::LammpsBondFeneExpand(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, DEFAULT_K);
        setParameter(R0_INDEX, DEFAULT_R0);
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
        setParameter(DELTA_INDEX, DEFAULT_DELTA);
    }

    LammpsBondFeneExpand::LammpsBondFeneExpand(int n,
                                               double k,
                                               double r0,
                                               double epsilon,
                                               double sigma,
                                               double delta) :
                                                  LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, k);
        setParameter(R0_INDEX, r0);
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(SIGMA_INDEX, sigma);
        setParameter(DELTA_INDEX, delta);
    }

    /*
     * getRange()
     */
    double LammpsBondFeneExpand::getRange() {
        printf("WARNING : LammpsBondFeneExpand::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondFeneExpand::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondFeneExpand::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondFeneExpand::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondFeneExpand::setBox() is NOT implemented yet.\n");
    }

}

