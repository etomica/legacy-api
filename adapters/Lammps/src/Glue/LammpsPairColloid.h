/*
 *  LammpsPairColloid.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_COLLOID_WRAPPER_H
#define LAMMPS_PAIR_COLLOID_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairColloid : public LammpsPair {

        public:
            /**
              * Creates a native Lammps pair_style of colloid.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_A      = 1000.0
              *   DEFAULT_SIGMA  = 1.0
              *   DEFAULT_D1     = 1.0
              *   DEFAULT_D2     = 1.0
              *   DEFAULT_CUTOFF = 2.5
              * @param n Number of bodies in the potential
              */
            LammpsPairColloid(int n);
            /**
              * Creates a native Lammps pair_style of colloid.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param a Lammps simulation pair_coeff a parameter.
              * @param sigma Lammps simulation pair_coeff sigma parameter.
              * @param d1 Lammps simulation pair_coeff d1 parameter.
              * @param d2 Lammps simulation pair_coeff d2 parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairColloid(int n, double a, double sigma, double d1,
                              double d2, double cutoff);		

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
            static const int SIGMA_INDEX;
            static const int D1_INDEX;
            static const int D2_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_A;
            static const double DEFAULT_SIGMA;
            static const double DEFAULT_D1;
            static const double DEFAULT_D2;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
