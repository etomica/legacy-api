/*
 *  LammpsPairLennardJonesCutoffCoulombCutoff.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_LENNARD_JONES_CUTOFF_COULOMB_CUTOFF_WRAPPER_H
#define LAMMPS_PAIR_LENNARD_JONES_CUTOFF_COULOMB_CUTOFF_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairLennardJonesCutoffCoulombCutoff : public LammpsPair {

        public:			
            LammpsPairLennardJonesCutoffCoulombCutoff(int n);		
            LammpsPairLennardJonesCutoffCoulombCutoff(int n, double epsilon, double sigma,
                                                      double ljCutoff, double coulombCutofff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int EPSILON_INDEX;
            static const int SIGMA_INDEX;
            static const int LJ_CUTOFF_INDEX;
            static const int COULOMB_CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NCUTOFF;
            static const int    NPARMS;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_SIGMA;
            static const double DEFAULT_LJ_CUTOFF;
            static const double DEFAULT_COULOMB_CUTOFF;

    };

}
#endif
