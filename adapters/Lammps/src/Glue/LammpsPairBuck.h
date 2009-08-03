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
            LammpsPairBuck(int n);		
            LammpsPairBuck(int n, double a, double rho, double C, double cutoff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
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
