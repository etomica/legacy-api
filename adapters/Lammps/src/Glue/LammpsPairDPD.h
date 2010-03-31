/*
 *  LammpsPairDPD.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_DPD_WRAPPER_H
#define LAMMPS_PAIR_DPD_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairDPD : public LammpsPair {

        public:
            /**
              * Creates a native Lammps pair_style of DPD.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_A      = 3.0
              *   DEFAULT_GAMMA  = 1.0
              *   DEFAULT_CUTOFF = 1.0
              * @param n Number of bodies in the potential
              */
            LammpsPairDPD(int n);
            /**
              * Creates a native Lammps pair_style of DPD.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param a Lammps simulation pair_coeff a parameter.
              * @param gamma Lammps simulation pair_coeff gamma parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairDPD(int n, double a, double gamma, double cutoff);		

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
            static const int GAMMA_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_A;
            static const double DEFAULT_GAMMA;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
