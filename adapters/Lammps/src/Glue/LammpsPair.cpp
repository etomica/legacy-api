/*
 *  LammpsPairLennardJonesCutoff.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsPair.h"
#include "LammpsPotential.h"

namespace lammpswrappers
{

    LammpsPair::LammpsPair(int n, int nParms, const char *type) :
                                         LammpsPotential(n, nParms, type) {
    }

    LammpsPair::LammpsPair(int n, int nParms, int nC, const char *type) :
                                         LammpsPotential(n, nParms, nC, type) {
    }

    /*
     * getRange()
     */
    double LammpsPair::getRange() {
printf("LammpsPair::getRange() is NOT implemented.\n"); fflush(stdout);
// The next line is NOT correct
//        return mPair->cutforce;
    }

}

