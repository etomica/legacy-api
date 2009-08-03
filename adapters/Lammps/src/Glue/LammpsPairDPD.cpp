/*
 *  LammpsPairDPD.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPairDPD.h"

namespace lammpswrappers
{

    const char *const LammpsPairDPD::BOND_NAME = "dpd";
    const int LammpsPairDPD::A_INDEX = 0;
    const int LammpsPairDPD::GAMMA_INDEX = 1;
    const int LammpsPairDPD::CUTOFF_INDEX = 2;
    const int LammpsPairDPD::NPARMS = 3;
    const int LammpsPairDPD::NCUTOFF = 1;
    const double LammpsPairDPD::DEFAULT_A = 3.0;
    const double LammpsPairDPD::DEFAULT_GAMMA = 1.0;
    const double LammpsPairDPD::DEFAULT_CUTOFF = 1.0;

    LammpsPairDPD::LammpsPairDPD(int n) : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, DEFAULT_A);
        setParameter(GAMMA_INDEX, DEFAULT_GAMMA);
        setParameter(CUTOFF_INDEX, DEFAULT_CUTOFF);
    }

    LammpsPairDPD::LammpsPairDPD(int n,
                                     double a,
                                     double gamma,
                                     double cutoff) :
                                         LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(A_INDEX, a);
        setParameter(GAMMA_INDEX, gamma);
        setParameter(CUTOFF_INDEX, cutoff);
    }

    /*
     * energy()
     */
    double LammpsPairDPD::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairDPD::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairDPD::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairDPD::setBox() is NOT implemented yet.\n");
    }

}

