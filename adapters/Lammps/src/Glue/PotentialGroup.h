/*
 *  PotentialGroup.h
 *  API Glue
 *
 */

#ifndef POTENTIAL_GROUP_WRAPPER_H
#define POTENTIAL_GROUP_WRAPPER_H

#include <vector>

#include "IAPIPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * The PotentialGroup provides an easy way to specifiy atom interactions
      * within a molecule.
      */
    class PotentialGroup : public virtual IAPIPotential {

        public:			
            PotentialGroup(int n);		

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *);
            int nBody();
            void setBox(IAPIBox *);

            // Non-API methods
            void addPotential(IAPIPotential *potential, int idx1[], int idx2[], int nPairs);
// Change to atom types
            void addPotential(IAPIPotential *potential, int atomType1, int atomType2);
            int getPotentialCount();
            IAPIPotential *getPotential(int index);
            int getPairCount(int index);
            int getAtomIndex1(int potIndex, int bondIndex);
            int getAtomIndex2(int potIndex, int bondIndex);
 
        protected:
            int nBdy;

        private:
            std::vector<IAPIPotential *> potentialList;
            std::vector<int> pairCount;
            std::vector<int *> pairList1;
            std::vector<int *> pairList2;
    };
}
#endif
