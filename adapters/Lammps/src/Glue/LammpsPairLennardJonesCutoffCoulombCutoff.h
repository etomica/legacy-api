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
            /**
              * Creates a native Lammps pair_style of lj/cut/coul/cut.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_EPSILON        = 1.0
              *   DEFAULT_SIGMA          = 1.1
              *   DEFAULT_LJ_CUTOFF      = 2.5
              *   DEFAULT_COULOMB_CUTOFF = 5.0
              * @param n Number of bodies in the potential
              */
            LammpsPairLennardJonesCutoffCoulombCutoff(int n);
            /**
              * Creates a native Lammps pair_style of lj/cut/coul/cut.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param epsilon Lammps simulation pair_coeff epsilon
              *                parameter.
              * @param sigma Lammps simulation pair_coeff sigma parameter.
              * @param ljCutoff Lammps simulation pair_coeff cutoff1
              *                 parameter.
              * @param coulombCutoff Lammps simulation pair_coeff cutoff2
              *                      parameter.
              */
            LammpsPairLennardJonesCutoffCoulombCutoff(int n, double epsilon, double sigma,
                                                      double ljCutoff, double coulombCutoff);		

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

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
