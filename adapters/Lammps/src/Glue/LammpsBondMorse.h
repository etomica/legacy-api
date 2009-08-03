/*
 *  LammpsBondMorse.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_MORSE_WRAPPER_H
#define LAMMPS_BOND_MORSE_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondMorse : public LammpsPotential {

        public:			
            LammpsBondMorse(int n);		
            LammpsBondMorse(int n, double d, double alpha, double r0);

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int D_INDEX;
            static const int ALPHA_INDEX;
            static const int R0_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_D;
            static const double DEFAULT_ALPHA;
            static const double DEFAULT_R0;

    };
}
#endif
