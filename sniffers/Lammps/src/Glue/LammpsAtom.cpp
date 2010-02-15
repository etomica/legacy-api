/*
 *  LammpsAtom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"
#include "atom.h"

#include "LammpsAtom.h"

namespace lammpssnifferwrappers
{

    LammpsAtom::LammpsAtom(LammpsSimulation *sim, IAPIAtomType *at,
                           IAPIMolecule *mole, int nIndex) {
        init(sim, at, mole, nIndex);
    }

    /*
     * init()
     */
    void LammpsAtom::init(LammpsSimulation *sim, IAPIAtomType *at,
                          IAPIMolecule *mole, int nIndex) {

        mSim = sim;

        mAtomType = at;

        nativeIndex = nIndex;

        parent = mole;

        double **pos = (double **) malloc (1 * sizeof(double *));
        pos = &(mSim->getLammpsSim()->atom->x[nativeIndex]);
        mPosition = mSim->getSpace()->makeVector(pos);

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
        printf("ERROR : LammpsAtom::setParent(IAPIMolecule *) not implemented.\n");
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
