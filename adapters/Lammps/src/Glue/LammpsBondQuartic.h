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
            LammpsBondQuartic(int n);		
            LammpsBondQuartic(int n, double k, double b1,
                           double b2, double rc, double u0);		

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
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
