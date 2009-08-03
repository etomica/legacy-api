/*
 *  LammpsPairLennardJonesCutoffCoulombCutoff.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairLennardJonesCutoffCoulombCutoff.h"

namespace lammpswrappers
{

    const char *const LammpsPairLennardJonesCutoffCoulombCutoff::BOND_NAME = "lj/cut";
    const int LammpsPairLennardJonesCutoffCoulombCutoff::EPSILON_INDEX = 0;
    const int LammpsPairLennardJonesCutoffCoulombCutoff::SIGMA_INDEX = 1;
    const int LammpsPairLennardJonesCutoffCoulombCutoff::LJ_CUTOFF_INDEX = 2;
    const int LammpsPairLennardJonesCutoffCoulombCutoff::COULOMB_CUTOFF_INDEX = 3;
    const int    LammpsPairLennardJonesCutoffCoulombCutoff::NCUTOFF = 2;
    const int    LammpsPairLennardJonesCutoffCoulombCutoff::NPARMS = 4;
    const double LammpsPairLennardJonesCutoffCoulombCutoff::DEFAULT_EPSILON = 1.0;
    const double LammpsPairLennardJonesCutoffCoulombCutoff::DEFAULT_SIGMA = 1.1;
    const double LammpsPairLennardJonesCutoffCoulombCutoff::DEFAULT_LJ_CUTOFF = 2.5;
    const double LammpsPairLennardJonesCutoffCoulombCutoff::DEFAULT_COULOMB_CUTOFF = 5.0;

    LammpsPairLennardJonesCutoffCoulombCutoff::LammpsPairLennardJonesCutoffCoulombCutoff(int n) :
                                                  LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, DEFAULT_EPSILON);
        setParameter(SIGMA_INDEX, DEFAULT_SIGMA);
        setParameter(LJ_CUTOFF_INDEX, DEFAULT_LJ_CUTOFF);
        setParameter(COULOMB_CUTOFF_INDEX, DEFAULT_COULOMB_CUTOFF);
    }

    LammpsPairLennardJonesCutoffCoulombCutoff::LammpsPairLennardJonesCutoffCoulombCutoff
                                    (int n,
                                     double epsilon,
                                     double sigma,
                                     double ljCutoff,
                                     double coulombCutoff) :
                                   LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(EPSILON_INDEX, epsilon);
        setParameter(SIGMA_INDEX, sigma);
        setParameter(LJ_CUTOFF_INDEX, ljCutoff);
        setParameter(COULOMB_CUTOFF_INDEX, coulombCutoff);
    }

    /*
     * energy()
     */
    double LammpsPairLennardJonesCutoffCoulombCutoff::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairLennardJonesCutoffCoulombCutoff::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairLennardJonesCutoffCoulombCutoff::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairLennardJonesCutoffCoulombCutoff::setBox() is NOT implemented yet.\n");
    }

}

