/*
 *  LammpsBondHarmonic.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"

#include "LammpsPotential.h"
#include "LammpsBondHarmonic.h"

namespace lammpswrappers
{

    const char *const LammpsBondHarmonic::BOND_NAME = "harmonic";
    const int LammpsBondHarmonic::K_INDEX = 0;
    const int LammpsBondHarmonic::R0_INDEX = 1;
    const int    LammpsBondHarmonic::NPARMS = 2;
    const double LammpsBondHarmonic::DEFAULT_K = 1000.0;
    const double LammpsBondHarmonic::DEFAULT_R0 = 1.0;

    LammpsBondHarmonic::LammpsBondHarmonic(int n) : LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, DEFAULT_K);
        setParameter(R0_INDEX, DEFAULT_R0);
    }

    LammpsBondHarmonic::LammpsBondHarmonic(int n, double k_val, double r0_val) :
                                               LammpsPotential(n, NPARMS, BOND_NAME) {
        setParameter(K_INDEX, k_val);
        setParameter(R0_INDEX, r0_val);
    }

    /*
     * getRange()
     */
    double LammpsBondHarmonic::getRange() {
        printf("WARNING : LammpsBondHarmonic::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double LammpsBondHarmonic::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsBondHarmonic::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsBondHarmonic::setBox(IAPIBox *b) {
        printf("WARNING : LammpsBondHarmonic::setBox() is NOT implemented yet.\n");
    }

}
  

