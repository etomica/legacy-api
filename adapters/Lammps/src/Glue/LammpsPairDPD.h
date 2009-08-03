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
            LammpsPairDPD(int n);		
            LammpsPairDPD(int n, double a, double gamma, double cutoff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
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
