/*
 *  LammpsBondFene.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_FENE_WRAPPER_H
#define LAMMPS_BOND_FENE_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondFene : public LammpsPotential {

        public:			
            LammpsBondFene(int n);		
            LammpsBondFene(int n, double k, double r0,
                           double epsilon, double sigma);		

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int K_INDEX;
            static const int R0_INDEX;
            static const int EPSILON_INDEX;
            static const int SIGMA_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_K;
            static const double DEFAULT_R0;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_SIGMA;

    };
}
#endif
