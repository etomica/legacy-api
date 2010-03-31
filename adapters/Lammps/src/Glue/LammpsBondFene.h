/*
 *  LammpsBondFene.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_FENE_WRAPPER_H
#define LAMMPS_BOND_FENE_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondFene : public LammpsPotential {

        public:
            /**
              * Creates a native lammps bond_style of fene.
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   K       = 10000.0;
              *   R0      = 1.0;
              *   EPSILON = 1.0;
              *   SIGMA   = 1.0;
              * @param n Number of bodies in the potential
              */
            LammpsBondFene(int n);
            /**
              * Creates a native lammps bond_style of fene.
              * @param n Number of bodies in the potential
              * @param k Native Lammps simulation bond_coeff k parameter.
              * @param r0 Native Lammps simulation bond_coeff r0 parameter.
              * @param epsilon Native Lammps simulation bond_coeff epsilon parameter.
              * @param sigma Native Lammps simulation bond_coeff sigma parameter.
              */
            LammpsBondFene(int n, double k, double r0,
                           double epsilon, double sigma);		

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
            static const int EPSILON_INDEX;
            static const int SIGMA_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_K;
            static const double DEFAULT_R0;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_SIGMA;

    };
}
#endif
