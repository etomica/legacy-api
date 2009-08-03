/*
 *  LammpsPairMorse.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_MORSE_WRAPPER_H
#define LAMMPS_PAIR_MORSE_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairMorse : public LammpsPair {

        public:			
            LammpsPairMorse(int n);		
            LammpsPairMorse(int n, double d0, double alpha, double r0, double cutoff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int D0_INDEX;
            static const int ALPHA_INDEX;
            static const int R0_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_D0;
            static const double DEFAULT_ALPHA;
            static const double DEFAULT_R0;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
