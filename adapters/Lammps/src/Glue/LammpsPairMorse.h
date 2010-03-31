/*
 *  LammpsPairMorse.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_MORSE_WRAPPER_H
#define LAMMPS_PAIR_MORSE_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairMorse : public LammpsPair {

        public:
            /**
              * Creates a native Lammps pair_style of morse.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_D0      = 1.0
              *   DEFAULT_ALPHA   = 1.1
              *   DEFAULT_R0      = 2.5
              *   DEFAULT__CUTOFF = 5.0
              * @param n Number of bodies in the potential
              */
            LammpsPairMorse(int n);
            /**
              * Creates a native Lammps pair_style of lj/cut/coul/cut.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param d0 Lammps simulation pair_coeff d0 parameter.
              * @param alpha Lammps simulation pair_coeff alpha parameter.
              * @param r0 Lammps simulation pair_coeff r0 parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairMorse(int n, double d0, double alpha, double r0, double cutoff);		

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

            static const int D0_INDEX;
            static const int ALPHA_INDEX;
            static const int R0_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_D0;
            static const double DEFAULT_ALPHA;
            static const double DEFAULT_R0;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
