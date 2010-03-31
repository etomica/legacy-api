/*
 *  LammpsBondClass2.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_CLASS2_WRAPPER_H
#define LAMMPS_BOND_CLASS2_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondClass2 : public LammpsPotential {

        public:
            /**
              * Creates a native lammps bond_style of class2.
              * Bond parameters (native Lammps simulation bond_coeff command):
              *   R0 = 1.0;
              *   K2 = 1.0;
              *   K3 = 1.0;
              *   K4 = 1.0
              * @param n Number of bodies in the potential
              */
            LammpsBondClass2(int n);		
            /**
              * Creates a native lammps bond_style of class2.
              * @param n Number of bodies in the potential
              * @param r0 Native Lammps simulation bond_coeff r0 parameter.
              * @param k2 Native Lammps simulation bond_coeff k2 parameter.
              * @param k3 Native Lammps simulation bond_coeff k3 parameter.
              * @param k4 Native Lammps simulation bond_coeff k4 parameter.
              */
            LammpsBondClass2(int n, double r0, double k2, double k3, double k4);

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
            static const int R0_INDEX;
            static const int K2_INDEX;
            static const int K3_INDEX;
            static const int K4_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_R0;
            static const double DEFAULT_K2;
            static const double DEFAULT_K3;
            static const double DEFAULT_K4;

    };
}
#endif
