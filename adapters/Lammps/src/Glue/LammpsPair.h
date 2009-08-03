/*
 *  LammpsPair.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_WRAPPER_H
#define LAMMPS_PAIR_WRAPPER_H

#include "IAPIPotentialAtomic.h"
#include "LammpsPotential.h"

#include "pair.h"

using namespace molesimAPI;
using namespace LAMMPS_NS;

namespace lammpswrappers
{

    class LammpsPair : public LammpsPotential,
                       public virtual IAPIPotentialAtomic {

        public:			
            LammpsPair(int n, int nParms, const char *type);		
            LammpsPair(int n, int nParms, int nC, const char *type);		

            // API methods
            virtual double energy(IAPIAtomList *) = 0;
            double getRange();

            // Non-API methods
            void setLammpsPair(LAMMPS_NS::Pair *pair);

        protected:
            LAMMPS_NS::Pair *mPair;

    };
}
#endif
