/*
 *  LammpsPairLennardJonesExpand.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_LENNARD_JONES_EXPAND_WRAPPER_H
#define LAMMPS_PAIR_LENNARD_JONES_EXPAND_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairLennardJonesExpand : public LammpsPair {

        public:
            /**
              * Creates a native Lammps pair_style of lj/expand.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              *   DEFAULT_EPSILON        = 1.0
              *   DEFAULT_SIGMA          = 1.1
              *   DEFAULT_DELTA          = 0.5
              *   DEFAULT_LJ_CUTOFF      = 2.5
              * @param n Number of bodies in the potential
              */
            LammpsPairLennardJonesExpand(int n);
            /**
              * Creates a native Lammps pair_style of lj/cut/coul/cut.
              * Pair parameters (native Lammps simulation pair_coeff
              * command) :
              * @param n Number of bodies in the potential
              * @param epsilon Lammps simulation pair_coeff epsilon
              *                parameter.
              * @param sigma Lammps simulation pair_coeff sigma parameter.
              * @param delta Lammps simulation pair_coeff delta parameter.
              * @param ljCutoff Lammps simulation pair_coeff cutoff1
              *                 parameter.
              */
            LammpsPairLennardJonesExpand(int n, double epsilon, double sigma,
                                         double delta, double ljCutoff);		

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

            static const int EPSILON_INDEX;
            static const int SIGMA_INDEX;
            static const int DELTA_INDEX;
            static const int LJ_CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_SIGMA;
            static const double DEFAULT_DELTA;
            static const double DEFAULT_LJ_CUTOFF;

    };

}
#endif
