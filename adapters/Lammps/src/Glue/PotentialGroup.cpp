/*
 *  PotentialGroup.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "library.h"

#include "PotentialGroup.h"

namespace lammpswrappers
{

    PotentialGroup::PotentialGroup(int n) {
        nBdy = n;
    }

    /*
     * getRange()
     */
    double PotentialGroup::getRange() {
        printf("WARNING : PotentialGroup::getRange() is NOT implemented yet.\n");
    }

    /*
     * energy()
     */
    double PotentialGroup::energy(IAPIAtomList *as) {
        printf("WARNING : PotentialGroup::energy() is NOT implemented yet.\n");
    }

    /*
     * nBody()
     */
    int PotentialGroup::nBody() {
        return nBdy;
    }

    /*
     * setBox()
     */
    void PotentialGroup::setBox(IAPIBox *b) {
        printf("WARNING : PotentialGroup::setBox() is NOT implemented yet.\n");
    }

    /*
     * addPotential()
     */
    void PotentialGroup::addPotential(IAPIPotential *potential, int idx1[], int idx2[], int nPairs) {
        potentialList.push_back(potential);
        pairCount.push_back(nPairs);
        int *l1 = (int *) malloc (nPairs * sizeof(int));
        int *l2 = (int *) malloc (nPairs * sizeof(int));
        for(int i = 0; i < nPairs; i++) {
            l1[i] = idx1[i];
            l2[i] = idx2[i];
        }
        pairList1.push_back(l1);
        pairList2.push_back(l2);
    }

    /*
     * addPotential()
     */
    void PotentialGroup::addPotential(IAPIPotential *potential, int atomType1, int atomType2) {
        int idx1[] = {atomType1};
        int idx2[] = {atomType2};
        addPotential(potential, idx1, idx2, 1);
    }

    /*
     * getPotentialCount()
     */
    int PotentialGroup::getPotentialCount() {
        return potentialList.size();
    }

    /*
     * getPotential()
     */
    IAPIPotential *PotentialGroup::getPotential(int index) {
        return potentialList.at(index);
    }

    /*
     * getPairCount()
     */
    int PotentialGroup::getPairCount(int index) {
        return pairCount.at(index);
    }

    /*
     * getAtomIndex1()
     */
    int PotentialGroup::getAtomIndex1(int potIndex, int bondIndex) {
        return pairList1.at(potIndex)[bondIndex];
    }

    /*
     * getAtomIndex2()
     */
    int PotentialGroup::getAtomIndex2(int potIndex, int bondIndex) {
        return pairList2.at(potIndex)[bondIndex];
    }

}

