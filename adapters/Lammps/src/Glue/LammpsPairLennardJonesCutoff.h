/*
 *  LammpsPairLennardJonesCutoff.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_LENNARD_JONES_CUTOFF_WRAPPER_H
#define LAMMPS_PAIR_LENNARD_JONES_CUTOFF_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairLennardJonesCutoff : public LammpsPair {

        public:			
            LammpsPairLennardJonesCutoff(int n);		
            LammpsPairLennardJonesCutoff(int n, double epsilon, double sigma, double ljCutoff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int EPSILON_INDEX;
            static const int SIGMA_INDEX;
            static const int LJ_CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_SIGMA;
            static const double DEFAULT_LJ_CUTOFF;

    };

}
#endif