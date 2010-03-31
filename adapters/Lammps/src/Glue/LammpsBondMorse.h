/*
 *  LammpsBondMorse.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_MORSE_WRAPPER_H
#define LAMMPS_BOND_MORSE_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondMorse : public LammpsPotential {

        public:
            /**
              * Creates a native lammps bond_style of morse.
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   D     = 1.0;
              *   ALPHA = 1.0;
              *   R0    = 1.0;
              * @param n Number of bodies in the potential
              */
            LammpsBondMorse(int n);
            /**
              * Creates a native lammps bond_style of morse.
              * @param n Number of bodies in the potential
              * @param d Native Lammps simulation bond_coeff d parameter.
              * @param alpha Native Lammps simulation bond_coeff alpha parameter.
              * @param r0 Native Lammps simulation bond_coeff r0 parameter.
              */
            LammpsBondMorse(int n, double d, double alpha, double r0);

            // API Compliance
            /**
              * This method is not implemented.
              */
            double getRange();
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

            // Non-API methods
            static const int D_INDEX;
            static const int ALPHA_INDEX;
            static const int R0_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_D;
            static const double DEFAULT_ALPHA;
            static const double DEFAULT_R0;

    };
}
#endif
