/*
 *  LammpsBondNonlinear.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_NONLINEAR_WRAPPER_H
#define LAMMPS_BOND_NONLINEAR_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondNonlinear : public LammpsPotential {

        public:			
            LammpsBondNonlinear(int n);		
            LammpsBondNonlinear(int n, double epsilon, double r0, double lambda);

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int EPSILON_INDEX;
            static const int R0_INDEX;
            static const int LAMBDA_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_EPSILON;
            static const double DEFAULT_R0;
            static const double DEFAULT_LAMBDA;

    };
}
#endif
