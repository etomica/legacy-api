/*
 *  LammpsPairColloid.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairColloid.h"

namespace lammpswrappers
{

    const char *const LammpsPairColloid::BOND_NAME = "colloid";
    const int LammpsPairColloid::A_INDEX = 0;
    const int LammpsPairColloid::SIGMA_INDEX = 1;
    const int LammpsPairColloid::D1_INDEX = 2;
    const int LammpsPairColloid::D2_INDEX = 3;
    const int LammpsPairColloid::CUTOFF_INDEX = 4;
    const int    LammpsPairColloid::NPARMS = 5;
    const int    LammpsPairColloid::NCUTOFF = 1;
    const double LammpsPairColloid::DEFAULT_A = 1000.0;
    const double LammpsPairColloid::DEFAULT_SIGMA = 1.0;
    const double LammpsPairColloid::DEFAULT_D1 = 1.0;
    const double LammpsPairColloid::DEFAULT_D2 = 1.0;
    const double LammpsPairColloid::DEFAULT_CUTOFF = 2.5;

    LammpsPairColloid::LammpsPairColloid(int n) : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, DEFAULT_A);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
        setParameter(D1_INDEX, DEFAULT_D1);
        setParameter(D2_INDEX, DEFAULT_D2);
        setParameter(CUTOFF_INDEX, DEFAULT_CUTOFF);
    }

    LammpsPairColloid::LammpsPairColloid(int n,
                                     double a,
                                     double sigma,
                                     double d1,
                                     double d2,
                                     double cutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, a);
        setParameter(SIGMA_INDEX, sigma);
        setParameter(D1_INDEX, d1);
        setParameter(D2_INDEX, d2);
        setParameter(CUTOFF_INDEX, cutoff);
    }

    /*
     * energy()
     */
    double LammpsPairColloid::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairColloid::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairColloid::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairColloid::setBox() is NOT implemented yet.\n");
    }

}

