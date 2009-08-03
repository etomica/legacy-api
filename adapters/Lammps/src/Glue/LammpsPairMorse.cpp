/*
 *  LammpsPairMorse.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairMorse.h"

namespace lammpswrappers
{

    const char *const LammpsPairMorse::BOND_NAME = "morse";
    const int LammpsPairMorse::D0_INDEX = 0;
    const int LammpsPairMorse::ALPHA_INDEX = 1;
    const int LammpsPairMorse::R0_INDEX = 2;
    const int LammpsPairMorse::CUTOFF_INDEX = 3;
    const int LammpsPairMorse::NPARMS = 4;
    const int LammpsPairMorse::NCUTOFF = 1;
    const double LammpsPairMorse::DEFAULT_D0 = 1000.0;
    const double LammpsPairMorse::DEFAULT_ALPHA = 2.0;
    const double LammpsPairMorse::DEFAULT_R0 = 1.0;
    const double LammpsPairMorse::DEFAULT_CUTOFF = 2.5;

    LammpsPairMorse::LammpsPairMorse(int n) : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(D0_INDEX, DEFAULT_D0);
        setParameter(ALPHA_INDEX, DEFAULT_ALPHA);
        setParameter(R0_INDEX, DEFAULT_R0);
        setParameter(CUTOFF_INDEX, DEFAULT_CUTOFF);
    }

    LammpsPairMorse::LammpsPairMorse(int n,
                                     double d0,
                                     double alpha,
                                     double r0,
                                     double cutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(D0_INDEX, d0);
        setParameter(ALPHA_INDEX, alpha);
        setParameter(R0_INDEX, r0);
        setParameter(CUTOFF_INDEX, cutoff);
    }

    /*
     * energy()
     */
    double LammpsPairMorse::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairMorse::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairMorse::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairMorse::setBox() is NOT implemented yet.\n");
    }

}

