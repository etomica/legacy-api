/*
 *  LammpsPairLennardJonesExpand.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairLennardJonesExpand.h"

namespace lammpswrappers
{

    const char *const LammpsPairLennardJonesExpand::BOND_NAME = "lj/expand";
    const int LammpsPairLennardJonesExpand::EPSILON_INDEX = 0;
    const int LammpsPairLennardJonesExpand::SIGMA_INDEX = 1;
    const int LammpsPairLennardJonesExpand::DELTA_INDEX = 2;
    const int LammpsPairLennardJonesExpand::LJ_CUTOFF_INDEX = 3;
    const int LammpsPairLennardJonesExpand::NPARMS = 4;
    const int LammpsPairLennardJonesExpand::NCUTOFF = 1;
    const double LammpsPairLennardJonesExpand::DEFAULT_EPSILON = 1.0;
    const double LammpsPairLennardJonesExpand::DEFAULT_SIGMA = 1.1;
    const double LammpsPairLennardJonesExpand::DEFAULT_DELTA = 0.5;
    const double LammpsPairLennardJonesExpand::DEFAULT_LJ_CUTOFF = 2.5;

    LammpsPairLennardJonesExpand::LammpsPairLennardJonesExpand(int n) :
                                   LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
        setParameter(DELTA_INDEX, DEFAULT_DELTA);
        setParameter(LJ_CUTOFF_INDEX, DEFAULT_LJ_CUTOFF);
    }

    LammpsPairLennardJonesExpand::LammpsPairLennardJonesExpand(int n,
                                     double epsilon,
                                     double sigma,
                                     double delta,
                                     double ljCutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(SIGMA_INDEX, sigma);
        setParameter(DELTA_INDEX, delta);
        setParameter(LJ_CUTOFF_INDEX, ljCutoff);
    }

    /*
     * energy()
     */
    double LammpsPairLennardJonesExpand::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairLennardJonesExpand::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairLennardJonesExpand::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairLennardJonesExpand::setBox() is NOT implemented yet.\n");
    }

}

