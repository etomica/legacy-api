/*
 *  LammpsBondNonlinear.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_NONLINEAR_WRAPPER_H
#define LAMMPS_BOND_NONLINEAR_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondNonlinear : public LammpsPotential {

        public:
            /**
              * Creates a native lammps bond_style of nonlinear.
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   EPSILON = 100.0;
              *   R0      = 1.0;
              *   LAMBDA  = 1.5;
              * @param n Number of bodies in the potential
              */
            LammpsBondNonlinear(int n);
            /**
              * Creates a native lammps bond_style of nonlinear.
              * @param n Number of bodies in the potential
              * @param epsilon Native Lammps simulation bond_coeff epsilon parameter.
              * @param r0 Native Lammps simulation bond_coeff r0 parameter.
              * @param lambda Native Lammps simulation bond_coeff lambda parameter.
              */
            LammpsBondNonlinear(int n, double epsilon, double r0, double lambda);

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
            static const int EPSILON_INDEX;
            static const int R0_INDEX;
            static const int LAMBDA_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_R0;
            static const double DEFAULT_LAMBDA;

    };
}
#endif
