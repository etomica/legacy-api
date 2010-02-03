/*
 *  LammpsAtom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"
#include "atom.h"

#include "LammpsAtom.h"
#include "LammpsAtomType.h"

namespace lammpssnifferwrappers
{

    LammpsAtom::LammpsAtom(LammpsSimulation *sim, IAPIAtomType *at, int nIndex) {
printf("DEBUG : New Atom : at index -> %d  nativeIndex -> %d\n", at->getIndex(), nIndex);
        mSim = sim;

        mAtomType = at;

        nativeIndex = nIndex;

        double **pos = (double **) malloc (1 * sizeof(double *));
        pos = &(mSim->getLammpsSim()->atom->x[nativeIndex]);
printf("ATOM MAIN : %x\n", &(mSim->getLammpsSim()->atom->x[nativeIndex]));
printf("  ATOM POSITION ADDRESS : %x  %x  %x\n",
        &mSim->getLammpsSim()->atom->x[nativeIndex][0],
        &mSim->getLammpsSim()->atom->x[nativeIndex][1],
        &mSim->getLammpsSim()->atom->x[nativeIndex][2]);
printf("    ATOM POSITION ADDRESS : %x  %x  %x\n",
        &(pos[0][0]), &(pos[0][1]), &(pos[0][2]));
printf("      ATOM POSITION ADDRESS : %x  %x  %x\n",
        &(*(pos)[0]), &(*(pos)[1]), &(*(pos)[2]));

        mPosition = mSim->getSpace()->makeVector(pos);

mSim->getLammpsSim()->atom->x[nativeIndex][0] = nativeIndex;
mSim->getLammpsSim()->atom->x[nativeIndex][1] = nativeIndex;
mSim->getLammpsSim()->atom->x[nativeIndex][2] = nativeIndex;
       
printf("%f  %f  %f\n", mPosition->getX(0), mPosition->getX(1), mPosition->getX(2)); fflush(stdout);
printf("  %f  %f  %f\n", pos[0][0],  pos[0][1],  pos[0][2]);
printf("    %f  %f  %f\n", (*pos)[0],  (*pos)[1],  (*pos)[2]);

        double **vel = (double **) malloc (1 * sizeof(double *));
        vel = &(mSim->getLammpsSim()->atom->v[nativeIndex]);
        mVel = mSim->getSpace()->makeVector(vel);

        double **force = (double **) malloc (1 * sizeof(double *));
        force = &(mSim->getLammpsSim()->atom->f[nativeIndex]);
        mForce = mSim->getSpace()->makeVector(force);

    }

    /*
     * getIndex()
     */
    int LammpsAtom::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void LammpsAtom::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getLeafIndex()
     */
    int LammpsAtom::getLeafIndex() {
        return mLeafIndex;
    }

    /*
     * setLeafIndex()
     */
    void LammpsAtom::setLeafIndex(int newGlobalIndex) {
        mLeafIndex = newGlobalIndex;
    }

    /*
     * setParent()
     */
    void LammpsAtom::setParent(IAPIMolecule *newParent) {
        parent = newParent;
    }

    /*
     * getParentGroup()
     */
    IAPIMolecule *LammpsAtom::getParentGroup() {
        return parent;
    }

    /*
     * getType()
     */
    IAPIAtomType *LammpsAtom::getType() {
        return mAtomType;
    }

    /*
     * getPosition()
     */
    IAPIVectorMutable *LammpsAtom::getPosition() {
//printf("Atom Position : %d  %f %f %f\n", nativeIndex, mPosition->getX(0), mPosition->getX(1), mPosition->getX(2)); fflush(stdout);
        return mPosition;
    }

    /*
     * getVelocity()
     */
    IAPIVectorMutable *LammpsAtom::getVelocity() {
        return mVel;
    }

    /*
     * getForce()
     */
    IAPIVectorMutable *LammpsAtom::getForce() {
        return mForce;
    }

    /*
     * getNativeIndex()
     */
    int LammpsAtom::getNativeIndex() {
        return nativeIndex;
    }

}
