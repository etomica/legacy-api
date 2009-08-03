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
            LammpsBondHarmonic(int n);		
            LammpsBondHarmonic(int n, double k_val, double r0_val);		

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
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
