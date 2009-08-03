/*
 *  LammpsPairLennardJonesCutoff.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairLennardJonesCutoff.h"

namespace lammpswrappers
{

    const char *const LammpsPairLennardJonesCutoff::BOND_NAME = "lj/cut";
    const int LammpsPairLennardJonesCutoff::EPSILON_INDEX = 0;
    const int LammpsPairLennardJonesCutoff::SIGMA_INDEX = 1;
    const int LammpsPairLennardJonesCutoff::LJ_CUTOFF_INDEX = 2;
    const int LammpsPairLennardJonesCutoff::NPARMS = 3;
    const int LammpsPairLennardJonesCutoff::NCUTOFF = 1;
    const double LammpsPairLennardJonesCutoff::DEFAULT_EPSILON = 1.0;
    const double LammpsPairLennardJonesCutoff::DEFAULT_SIGMA = 1.1;
    const double LammpsPairLennardJonesCutoff::DEFAULT_LJ_CUTOFF = 2.5;

    LammpsPairLennardJonesCutoff::LammpsPairLennardJonesCutoff(int n) :
                                  LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
        setParameter(LJ_CUTOFF_INDEX, DEFAULT_LJ_CUTOFF);
    }

    LammpsPairLennardJonesCutoff::LammpsPairLennardJonesCutoff(int n,
                                     double epsilon,
                                     double sigma,
                                     double ljCutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(SIGMA_INDEX, sigma);
        setParameter(LJ_CUTOFF_INDEX, ljCutoff);
    }

    /*
     * energy()
     */
    double LammpsPairLennardJonesCutoff::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairLennardJonesCutoff::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairLennardJonesCutoff::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairLennardJonesCutoff::setBox() is NOT implemented yet.\n");
    }

}

