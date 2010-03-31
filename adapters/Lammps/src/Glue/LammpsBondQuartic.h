/*
 *  LammpsBondQuartic.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_QUARTIC_WRAPPER_H
#define LAMMPS_BOND_QUARTIC_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondQuartic : public LammpsPotential {

        public:
            /**
              * Creates a native lammps bond_style of quartic.
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   K       = 10000.0;
              *   B1      = 10000.0;
              *   B2      = 10000.0;
              *   RC      = 1.0;
              *   U0      = 1.0;
              * @param n Number of bodies in the potential
              */
            LammpsBondQuartic(int n);
            /**
              * Creates a native lammps bond_style of quartic
              * @param n Number of bodies in the potential
              * @param k Native Lammps simulation bond_coeff k parameter.
              * @param b1 Native Lammps simulation bond_coeff b1 parameter.
              * @param b2 Native Lammps simulation bond_coeff b2 parameter.
              * @param rc Native Lammps simulation bond_coeff rc parameter.
              * @param u0 Native Lammps simulation bond_coeff u0 parameter.
              */
            LammpsBondQuartic(int n, double k, double b1,
                           double b2, double rc, double u0);		

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
            static const int K_INDEX ;
            static const int B1_INDEX;
            static const int B2_INDEX;
            static const int RC_INDEX;
            static const int U0_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_K;
            static const double DEFAULT_B1;
            static const double DEFAULT_B2;
            static const double DEFAULT_RC;
            static const double DEFAULT_U0;

    };
}
#endif
