/*
 *  LammpsBondClass2.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOND_CLASS2_WRAPPER_H
#define LAMMPS_BOND_CLASS2_WRAPPER_H


#include "LammpsPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBondClass2 : public LammpsPotential {

        public:			
            LammpsBondClass2(int n);		
            LammpsBondClass2(int n, double r0, double k2, double k3, double k4);

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            static const int R0_INDEX;
            static const int K2_INDEX;
            static const int K3_INDEX;
            static const int K4_INDEX;

        private:
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const double DEFAULT_R0;
            static const double DEFAULT_K2;
            static const double DEFAULT_K3;
            static const double DEFAULT_K4;

    };
}
#endif
