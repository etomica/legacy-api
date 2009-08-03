/*
 *  LammpsPairColloid.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_COLLOID_WRAPPER_H
#define LAMMPS_PAIR_COLLOID_WRAPPER_H


#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairColloid : public LammpsPair {

        public:			
            LammpsPairColloid(int n);		
            LammpsPairColloid(int n, double a, double sigma, double d1,
                              double d2, double cutoff);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int A_INDEX;
            static const int SIGMA_INDEX;
            static const int D1_INDEX;
            static const int D2_INDEX;
            static const int CUTOFF_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            static const double DEFAULT_A;
            static const double DEFAULT_SIGMA;
            static const double DEFAULT_D1;
            static const double DEFAULT_D2;
            static const double DEFAULT_CUTOFF;

    };

}
#endif
