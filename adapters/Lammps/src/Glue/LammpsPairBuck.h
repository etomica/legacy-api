/*
 *  LammpsPairBuck.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_BUCK_WRAPPER_H
#define LAMMPS_PAIR_BUCK_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairBuck : public LammpsPair {

        public:
            /**
              * Creates a native Lammps pair_style of buck.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_A      = 1000.0
              *   DEFAULT_RHO    = 2.0
              *   DEFAULT_C      = 1.0
              *   DEFAULT_CUTOFF = 2.5
              * @param n Number of bodies in the potential
              */
            LammpsPairBuck(int n);
            /**
              * Creates a native Lammps pair_style of buck.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param a Lammps simulation pair_coeff a parameter.
              * @param rho Lammps simulation pair_coeff rho parameter.
              * @param C Lammps simulation pair_coeff C parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairBuck(int n, double a, double rho, double C, double cutoff);		

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

            static const int A_INDEX;
            static const int RHO_INDEX;
            static const int C_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_A;
            static const double DEFAULT_RHO;
            static const double DEFAULT_C;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
