/*
 *  LammpsPairBuck.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairBuck.h"

namespace lammpswrappers
{

    const char *const LammpsPairBuck::BOND_NAME = "buck";
    const int LammpsPairBuck::A_INDEX = 0;
    const int LammpsPairBuck::RHO_INDEX = 1;
    const int LammpsPairBuck::C_INDEX = 2;
    const int LammpsPairBuck::CUTOFF_INDEX = 3;
    const int    LammpsPairBuck::NPARMS = 4;
    const int    LammpsPairBuck::NCUTOFF = 1;
    const double LammpsPairBuck::DEFAULT_A = 1000.0;
    const double LammpsPairBuck::DEFAULT_RHO = 2.0;
    const double LammpsPairBuck::DEFAULT_C = 1.0;
    const double LammpsPairBuck::DEFAULT_CUTOFF = 2.5;

    LammpsPairBuck::LammpsPairBuck(int n) : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, DEFAULT_A);
        setParameter(RHO_INDEX, DEFAULT_RHO);
        setParameter(C_INDEX, DEFAULT_C);
        setParameter(CUTOFF_INDEX, DEFAULT_CUTOFF);
    }

    LammpsPairBuck::LammpsPairBuck(int n,
                                   double a,
                                   double rho,
                                   double C,
                                   double cutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, a);
        setParameter(RHO_INDEX, rho);
        setParameter(C_INDEX, C);
        setParameter(CUTOFF_INDEX, cutoff);
    }

    /*
     * energy()
     */
    double LammpsPairBuck::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairBuck::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairBuck::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairBuck::setBox() is NOT implemented yet.\n");
    }

}

