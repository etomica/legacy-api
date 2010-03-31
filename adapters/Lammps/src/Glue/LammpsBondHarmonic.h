/*
 *  LammpsBondHarmonic.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_HARMONIC_WRAPPER_H
#define LAMMPS_BOND_HARMONIC_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondHarmonic : public LammpsPotential {

        public:			
            /**
              * Creates a native lammps bond_style of harmonic
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   K       = 1000.0;
              *   R0      = 1.0;
              * @param n Number of bodies in the potential
              */
            LammpsBondHarmonic(int n);
            /**
              * Creates a native lammps bond_style of harmonic.
              * @param n Number of bodies in the potential
              * @param k Native Lammps simulation bond_coeff k parameter.
              * @param r0 Native Lammps simulation bond_coeff r0 parameter.
              */
            LammpsBondHarmonic(int n, double k_val, double r0_val);		

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
            static const int K_INDEX;
            static const int R0_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_K;
            static const double DEFAULT_R0;

    };

}
#endif
