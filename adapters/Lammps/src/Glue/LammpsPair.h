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
            /**
              * Stores the kind of pair and pair parameters for construction
              * of a native Lammps pair_style command.  The number of
              * cutoffs is set to 0.
              * @param n Number of bodies in the potential
              * @param nParms Number of parameters relevant to the pair
              * @param type The type of pair
              */
            LammpsPair(int n, int nParms, const char *type);
            /**
              * Stores the kind of pair and pair parameters for construction
              * of a native Lammps pair_style command.
              * @param n Number of bodies in the potential
              * @param nParms Number of parameters relevant to the pair
              * @param nc Number of cutoff parameters relevant to the pair
              * @param type The type of pair
              */
            LammpsPair(int n, int nParms, int nC, const char *type);		

            // API methods
            virtual double energy(IAPIAtomList *) = 0;
            /**
              * This method is not implemented.
              */
            double getRange();

        protected:
            LAMMPS_NS::Pair *mPair;

    };
}
#endif
